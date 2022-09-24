from matplotlib import pyplot
import pandas

CSV_FILENAME = r"output.csv"

def _read_csv(filename: str):
    data = pandas.read_csv(filename, delimiter=",")
    return data


if __name__ == '__main__':
    data = _read_csv(CSV_FILENAME)

    data.plot()
    pyplot.show()
