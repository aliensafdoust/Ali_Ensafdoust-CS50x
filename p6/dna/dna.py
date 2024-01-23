import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(400)
    # TODO: Read database file into a variable
    da_ta = []
    with open(sys.argv[1], "r") as mainfile:
        read = csv.DictReader(mainfile)
        for row in read:
            a = row
            da_ta.append(a)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as se:
        DNA_secu = se.read()

    secu_1 = list(da_ta[0].keys())[1:]
    # TODO: Find longest match of each STR in DNA sequence
    fin_aly = {}
    for p in secu_1:
        fin_aly[p] = longest_match(DNA_secu, p)

    # TODO: Check database for matching profiles
    for people in da_ta:
        mat = 0
        for i in secu_1:
            if int(people[i]) == fin_aly[i]:
                mat += 1
        if mat == len(secu_1):
            print(people["name"])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
