import csv
import requests
from collections import defaultdict

def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)
    # for row in reader:
    #     print(row["state"], row["cases"])

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)
    print(new_cases.items())

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    # dict = {}
    # l = []
    # for row in reader:
    #     cases = row["cases"]
    #     state = row["state"]
    #     l += cases
    #     dict[state] = l
    #     if len(dict[state]) > 14:
    #         del dict[state[0]]

    data_dict = defaultdict(list)
    for row in reader:
        state = row["state"]
        cases = row["cases"]
        data_dict[state].append(cases)
        list_len = data_dict[state]
        if len(list_len) > 14:
            del list_len[0]

    return data_dict


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for s in range(len(states)):
        x = new_cases[states[s]]
        x = [int(x) for x in x]
        x = x[7:14]
        last_14 = sum(x) / 7
        x = x[0:7]
        first_14 = sum(x) / 7
        try:
            avg = (last_14 - first_14) / first_14
        except ZeroDivisionError:
            print("cant divide by zero")
        print(f"{states[s]} had a 7-day average of {last_14:.0f} and increase of {avg:.0f}%.")


main()
