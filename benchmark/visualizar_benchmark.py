"""
visualizar_benchmark.py
Parsea resultados_benchmark.md y genera visualizaciones de rendimiento.
Uso: python visualizar_benchmark.py [ruta_al_md]
"""

import re
import sys
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
import seaborn as sns
from pathlib import Path

# ─────────────────────────────────────────────
# 1. PARSEO DEL MARKDOWN
# ─────────────────────────────────────────────

def parse_benchmark_md(filepath: str) -> pd.DataFrame:
    text = Path(filepath).read_text(encoding="utf-8")
    rows = []

    # Secciones por tamaño de imagen
    img_sections = re.split(r"##\s+Imagen:\s+(\d+x\d+)", text)
    # img_sections[0] = header, luego pares (img_name, contenido)
    for i in range(1, len(img_sections), 2):
        img_size = img_sections[i]
        img_body = img_sections[i + 1]

        # Sub-secciones por filtro/posterizado
        sub_sections = re.split(
            r"###\s+Filtro:\s+([\dx]+),\s+Posterizado:\s+([\w\s]+)", img_body
        )
        for j in range(1, len(sub_sections), 3):
            filtro    = sub_sections[j].strip()
            poster    = sub_sections[j + 1].strip()
            table_txt = sub_sections[j + 2]

            # Extraer filas de tabla markdown
            for line in table_txt.splitlines():
                line = line.strip()
                if not line.startswith("|") or "---" in line or "Implementación" in line:
                    continue
                cols = [c.strip() for c in line.split("|")[1:-1]]
                if len(cols) < 4:
                    continue
                impl, config, tiempo_s, speedup_s = cols[:4]
                try:
                    tiempo   = float(tiempo_s)
                    speedup  = float(speedup_s.replace("x", ""))
                except ValueError:
                    continue

                rows.append({
                    "imagen":   img_size,
                    "filtro":   filtro,
                    "poster":   poster,
                    "impl":     impl,
                    "config":   config,
                    "tiempo":   tiempo,
                    "speedup":  speedup,
                })

    return pd.DataFrame(rows)


def escenario_label(row):
    """Etiqueta compacta para un escenario (imagen+filtro+poster)."""
    img = row["imagen"].replace("x", "×")
    return f"{img}\n{row['filtro']} | {row['poster']}"


def impl_label(row):
    """Etiqueta compacta para implementación+config."""
    if row["impl"] == "Secuencial":
        return "Seq"
    return f"{row['impl']}\n{row['config']}"


# ─────────────────────────────────────────────
# 2. PALETA Y ESTILO
# ─────────────────────────────────────────────

PALETTE = {
    "Secuencial": "#9e9e9e",
    "OpenMP":     "#1976d2",
    "MPI":        "#388e3c",
    "Híbrido":    "#f57c00",
}

def impl_color(impl):
    return PALETTE.get(impl, "#555")


# ─────────────────────────────────────────────
# 3. FIGURA 1 — HEATMAP DE SPEEDUP
# ─────────────────────────────────────────────

def fig_heatmap(df: pd.DataFrame, output: str):
    # Una fila por config, una col por escenario
    df2 = df[df["impl"] != "Secuencial"].copy()
    df2["escenario"] = df2.apply(escenario_label, axis=1)
    df2["impl_cfg"]  = df2.apply(impl_label, axis=1)

    # Orden de filas: OpenMP → MPI → Híbrido
    order_impl = sorted(df2["impl_cfg"].unique().tolist(), key=sort_key_impl_cfg_str)
    escenarios_order = sorted(df2["escenario"].unique().tolist(), key=sort_key_escenario)
    # Orden de columnas: 800 → 2000 → 5000, dentro cada uno 3x3/5x5 y 3/9 rangos
    escenarios_order = df2["escenario"].unique().tolist()

    pivot = df2.pivot_table(
        index="impl_cfg", columns="escenario",
        values="speedup", aggfunc="mean"
    )
    pivot = pivot.reindex(index=order_impl, columns=escenarios_order)

    fig, ax = plt.subplots(figsize=(16, 6))
    sns.heatmap(
        pivot, ax=ax,
        annot=True, fmt=".2f",
        cmap="YlOrRd",
        linewidths=0.4, linecolor="#ddd",
        cbar_kws={"label": "Speedup", "shrink": 0.8},
        vmin=0.9, vmax=pivot.values.max() + 0.1,
    )

    # Líneas divisoras entre grupos de implementación
    dividers = [
        len(df2[df2["impl"] == "OpenMP"]["impl_cfg"].unique()),
        len(df2[df2["impl"] == "OpenMP"]["impl_cfg"].unique()) +
        len(df2[df2["impl"] == "MPI"]["impl_cfg"].unique()),
    ]
    for d in dividers:
        ax.axhline(d, color="white", linewidth=2.5)

    # Etiquetas laterales de grupo
    group_centers = [
        len(df2[df2["impl"] == "OpenMP"]["impl_cfg"].unique()) / 2,
        len(df2[df2["impl"] == "OpenMP"]["impl_cfg"].unique()) +
        len(df2[df2["impl"] == "MPI"]["impl_cfg"].unique()) / 2,
        len(df2[df2["impl"] == "OpenMP"]["impl_cfg"].unique()) +
        len(df2[df2["impl"] == "MPI"]["impl_cfg"].unique()) +
        len(df2[df2["impl"] == "Híbrido"]["impl_cfg"].unique()) / 2,
    ]
    for center, label, color in zip(
        group_centers,
        ["OpenMP", "MPI", "Híbrido"],
        [PALETTE["OpenMP"], PALETTE["MPI"], PALETTE["Híbrido"]],
    ):
        ax.text(
            -0.7, center, label,
            ha="right", va="center", fontsize=10, fontweight="bold", color=color,
            transform=ax.get_yaxis_transform(),
        )

    ax.set_title("Heatmap de Speedup por Configuración y Escenario", fontsize=14, pad=14)
    ax.set_xlabel("Escenario (imagen · filtro · posterizado)", fontsize=10)
    ax.set_ylabel("")
    ax.tick_params(axis="x", labelsize=7.5)
    ax.tick_params(axis="y", labelsize=8)
    plt.tight_layout()
    plt.savefig(output, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  → {output}")


# ─────────────────────────────────────────────
# 4. FIGURA 2 — BARRAS: SPEEDUP POR TAMAÑO
# ─────────────────────────────────────────────

def fig_barras_por_tamano(df: pd.DataFrame, output: str):
    imagenes = df["imagen"].unique().tolist()
    fig, axes = plt.subplots(1, 3, figsize=(18, 5.5), sharey=False)

    for ax, img in zip(axes, imagenes):
        sub = df[df["imagen"] == img].copy()
        # Speedup promedio por impl+config (promediando filtro y posterizado)
        agg = (
            sub.groupby(["impl", "config"])["speedup"]
            .mean()
            .reset_index()
        )
        # Orden: Seq → OpenMP → MPI → Híbrido
        impl_order = ["Secuencial", "OpenMP", "MPI", "Híbrido"]
        agg["sort_key"] = agg.apply(sort_key_config, axis=1)
        agg = agg.sort_values("sort_key")
        agg["etiqueta"] = agg.apply(
            lambda r: "Seq" if r["impl"] == "Secuencial" else r["config"], axis=1
        )

        colors = [impl_color(r["impl"]) for _, r in agg.iterrows()]
        # Opacidad variable para configs dentro del mismo grupo
        alphas = []
        alpha_map = {"OpenMP": [0.5, 0.75, 1.0], "MPI": [0.5, 0.75, 1.0], "Híbrido": [0.6, 0.85, 1.0]}
        counts = {}
        for _, r in agg.iterrows():
            impl = r["impl"]
            idx = counts.get(impl, 0)
            if impl in alpha_map:
                a = alpha_map[impl][min(idx, len(alpha_map[impl]) - 1)]
            else:
                a = 1.0
            alphas.append(a)
            counts[impl] = idx + 1

        bars = ax.bar(
            range(len(agg)), agg["speedup"],
            color=colors,
            width=0.65, zorder=3,
        )
        # Aplicar alfas manualmente
        for bar, alpha in zip(bars, alphas):
            bar.set_alpha(alpha)

        # Línea de referencia speedup=1
        ax.axhline(1.0, color="#333", linewidth=1.0, linestyle="--", zorder=2)

        # Valores sobre barras
        for bar, val in zip(bars, agg["speedup"]):
            ax.text(
                bar.get_x() + bar.get_width() / 2,
                bar.get_height() + 0.01,
                f"{val:.2f}×",
                ha="center", va="bottom", fontsize=7, color="#222",
            )

        ax.set_xticks(range(len(agg)))
        ax.set_xticklabels(agg["etiqueta"], rotation=35, ha="right", fontsize=8)
        ax.set_title(f"Imagen {img.replace('x', '×')}", fontsize=11, fontweight="bold")
        ax.set_ylabel("Speedup promedio" if img == imagenes[0] else "")
        ax.set_xlabel("Configuración")
        ax.yaxis.set_minor_locator(mticker.AutoMinorLocator())
        ax.grid(axis="y", linestyle="--", alpha=0.4, zorder=0)
        ax.set_ylim(0, agg["speedup"].max() * 1.18)

    # Leyenda de colores
    from matplotlib.patches import Patch
    legend_elements = [
        Patch(facecolor=PALETTE[k], label=k) for k in ["OpenMP", "MPI", "Híbrido"]
    ]
    fig.legend(
        handles=legend_elements, loc="upper center",
        ncol=3, fontsize=10, frameon=True,
        bbox_to_anchor=(0.5, 1.02),
    )
    fig.suptitle(
        "Speedup promedio por configuración (promediado sobre filtros y posterizados)",
        fontsize=13, y=1.06,
    )
    plt.tight_layout()
    plt.savefig(output, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  → {output}")


# ─────────────────────────────────────────────
# 5. FIGURA 3 — EFICIENCIA PARALELA
# ─────────────────────────────────────────────

def recursos(impl, config):
    """Número total de 'recursos' (hilos o procs) según impl."""
    if impl == "Secuencial":
        return 1
    nums = re.findall(r"\d+", config)
    if impl == "Híbrido":
        return int(nums[0]) * int(nums[1]) if len(nums) >= 2 else None
    return int(nums[0]) if nums else None



def fig_eficiencia(df: pd.DataFrame, output: str):
    df2 = df[df["impl"] != "Secuencial"].copy()
    df2["recursos"] = df2.apply(lambda r: recursos(r["impl"], r["config"]), axis=1)
    df2["eficiencia"] = df2["speedup"] / df2["recursos"]

    # Promedio sobre todos los escenarios
    agg = (
        df2.groupby(["imagen", "impl", "config", "recursos"])["eficiencia"]
        .mean()
        .reset_index()
    )

    imagenes = df["imagen"].unique().tolist()
    fig, axes = plt.subplots(1, 3, figsize=(18, 5), sharey=True)

    for ax, img in zip(axes, imagenes):
        sub = agg[agg["imagen"] == img]
        for impl in ["OpenMP", "MPI", "Híbrido"]:
            s = sub[sub["impl"] == impl].sort_values("recursos")
            if s.empty:
                continue
            ax.plot(
                s["recursos"], s["eficiencia"],
                marker="o", label=impl,
                color=PALETTE[impl], linewidth=2, markersize=7,
            )
            for _, row in s.iterrows():
                ax.annotate(
                    row["config"],
                    (row["recursos"], row["eficiencia"]),
                    textcoords="offset points", xytext=(4, 4),
                    fontsize=6.5, color=PALETTE[impl],
                )

        ax.axhline(1.0, color="#333", linewidth=1.0, linestyle="--", label="Ideal")
        ax.set_title(f"Imagen {img.replace('x','×')}", fontsize=11, fontweight="bold")
        ax.set_xlabel("Recursos totales (hilos o procs)")
        if img == imagenes[0]:
            ax.set_ylabel("Eficiencia paralela (speedup / recursos)")
        ax.set_ylim(0, 1.15)
        ax.grid(linestyle="--", alpha=0.4)
        ax.legend(fontsize=8)

    fig.suptitle(
        "Eficiencia paralela promedio (ideal = 1.0)",
        fontsize=13,
    )
    plt.tight_layout()
    plt.savefig(output, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  → {output}")


# ─────────────────────────────────────────────
# 6. FIGURA 4 — SPEEDUP vs. TAMAÑO DE IMAGEN
# ─────────────────────────────────────────────

def fig_escalabilidad(df: pd.DataFrame, output: str):
    """
    Para las mejores configs de cada impl, muestra cómo evoluciona el speedup
    al aumentar el tamaño de la imagen.
    """
    # Mejor config de cada impl (max speedup promedio)
    df2 = df[df["impl"] != "Secuencial"].copy()
    agg = (
        df2.groupby(["impl", "config"])["speedup"]
        .mean()
        .reset_index()
    )
    best = agg.loc[agg.groupby("impl")["speedup"].idxmax()]

    img_order = ["800x800", "2000x2000", "5000x5000"]
    img_pixels = [800**2, 2000**2, 5000**2]

    fig, ax = plt.subplots(figsize=(9, 5))
    for _, row in best.iterrows():
        impl, config = row["impl"], row["config"]
        sub = (
            df2[(df2["impl"] == impl) & (df2["config"] == config)]
            .groupby("imagen")["speedup"].mean()
            .reindex(img_order)
        )
        ax.plot(
            img_pixels, sub.values,
            marker="o", label=f"{impl} ({config})",
            color=PALETTE[impl], linewidth=2.2, markersize=8,
        )

    ax.set_xscale("log")
    ax.set_xticks(img_pixels)
    ax.set_xticklabels(["800×800\n(640K px)", "2000×2000\n(4M px)", "5000×5000\n(25M px)"])
    ax.axhline(1.0, color="#888", linewidth=1.0, linestyle=":")
    ax.set_xlabel("Tamaño de imagen (píxeles totales, escala log)")
    ax.set_ylabel("Speedup promedio")
    ax.set_title("Escalabilidad: mejor config de cada impl vs. tamaño de imagen", fontsize=12)
    ax.legend(fontsize=9, loc="upper right")
    ax.grid(linestyle="--", alpha=0.4)
    plt.tight_layout()
    plt.savefig(output, dpi=150, bbox_inches="tight")
    plt.close()
    print(f"  → {output}")


def sort_key_config(row_or_dict):
    """Genera una clave de ordenamiento numérico para las configuraciones."""
    impl = row_or_dict["impl"]
    config = row_or_dict["config"]
    if impl == "Secuencial":
        return (0, 0, 0)
    
    # Extraer todos los números en la cadena
    nums = [int(n) for n in re.findall(r"\d+", config)]
    if not nums:
        return (1 if impl == "OpenMP" else 2 if impl == "MPI" else 3, 0, 0)
    
    if impl == "OpenMP":
        return (1, nums[0], 0) # Ordenar por nro de hilos
    elif impl == "MPI":
        return (2, nums[0], 0) # Ordenar por nro de procesos
    elif impl == "Híbrido":
        p = nums[0]
        t = nums[1] if len(nums) > 1 else 1
        return (3, p, t)       # Ordenar por procesos, luego hilos
    return (4, 0, 0)

def sort_key_impl_cfg_str(cfg_str):
    """Clave de ordenamiento para cadenas 'Implementación\nConfiguración' en el heatmap."""
    parts = cfg_str.split("\n")
    impl = parts[0]
    config = parts[1] if len(parts) > 1 else ""
    
    nums = [int(n) for n in re.findall(r"\d+", config)]
    if not nums:
        return (1 if impl == "OpenMP" else 2 if impl == "MPI" else 3, 0, 0)
        
    if impl == "OpenMP":
        return (1, nums[0], 0)
    elif impl == "MPI":
        return (2, nums[0], 0)
    elif impl == "Híbrido":
        p = nums[0]
        t = nums[1] if len(nums) > 1 else 1
        return (3, p, t)
    return (4, 0, 0)

def sort_key_escenario(escenario_str):
    """Clave para ordenar escenarios (800x800, luego 2000x2000, etc.)."""
    parts = escenario_str.split("\n")
    img_part = parts[0]
    img_size = int(re.findall(r"\d+", img_part)[0]) if re.findall(r"\d+", img_part) else 0
    
    rest = parts[1] if len(parts) > 1 else ""
    filter_part = rest.split("|")[0].strip() if "|" in rest else ""
    filter_size = int(re.findall(r"\d+", filter_part)[0]) if re.findall(r"\d+", filter_part) else 0
    
    poster_part = rest.split("|")[1].strip() if "|" in rest and len(rest.split("|")) > 1 else ""
    poster_ranges = int(re.findall(r"\d+", poster_part)[0]) if re.findall(r"\d+", poster_part) else 0
    
    return (img_size, filter_size, poster_ranges)
# ─────────────────────────────────────────────
# MAIN
# ─────────────────────────────────────────────

if __name__ == "__main__":
    md_path = sys.argv[1] if len(sys.argv) > 1 else "resultados_benchmark.md"
    out_dir  = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("graficos_benchmark")
    out_dir.mkdir(exist_ok=True)

    # Nombre base del archivo de entrada, sin extension
    # Ej: "CJ-10.md" -> "CJ-10"
    #     "RC-1.md" -> "RC-1"
    prefijo = Path(md_path).stem

    print(f"Leyendo: {md_path}")
    df = parse_benchmark_md(md_path)
    print(f"  {len(df)} filas parseadas.\n")

    print("Generando gráficos...")
    fig_heatmap(df,             str(out_dir / f"{prefijo}-heatmap_speedup.png"))
    fig_barras_por_tamano(df,   str(out_dir / f"{prefijo}-barras_speedup.png"))
    fig_eficiencia(df,          str(out_dir / f"{prefijo}-eficiencia.png"))
    fig_escalabilidad(df,       str(out_dir / f"{prefijo}-escalabilidad.png"))

    print(f"\n✓ Gráficos guardados en '{out_dir}/' con prefijo '{prefijo}-'")