from matplotlib import pyplot
import pandas

SIMPLE_CSV_FILENAME = r"output.csv"
ALPHA_BETA_CSV_FILENAME = r"output_alpha_beta_filter.csv"

def _read_csv(filename: str):
    data = pandas.read_csv(filename, delimiter=",")
    return data


if __name__ == '__main__':
    simple_data = _read_csv(SIMPLE_CSV_FILENAME)
    alpha_beta_data = _read_csv(ALPHA_BETA_CSV_FILENAME)

    simple_data.plot(figsize=(12, 12/1.618))

    fig, axes = pyplot.subplots(nrows=2, sharex=True, figsize=(12, 12/1.618))
    axes[0].plot(alpha_beta_data["noise_sample"], label="Noisy Data")
    axes[0].plot(alpha_beta_data["smoothed_sample"], label="Smooth Estimate")
    axes[1].plot(alpha_beta_data["velocity"])

    axes[0].set_title("Positions")
    axes[1].set_title("Velocity Estimate")

    pyplot.show()
