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

    # simple_data.plot(figsize=(12, 12/1.618))
    alpha_beta_data.plot(
        y=["noise_sample", "smoothed_sample"],
        figsize=(12, 12/1.618)
    )

    pyplot.show()
