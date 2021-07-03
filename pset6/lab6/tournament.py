# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage in commandline
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    # A list called teams (which will eventually be a list of teams)
    # DONE: Read teams into memory from file
    # In Python, to append to the end of a list, use the .append() function.
    teams = []

    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for team in reader:
            team['rating'] = int(team['rating'])
            teams.append(team)

    # a dictionary called counts (which will associate team names with the number of times that team won a simulated tournament).
    counts = {}
    # TODO: Simulate N tournaments and keep track of win counts
    # Keep track of win counts in the counts dictionary
    for i in range(N):
        ultimate_winner = simulate_tournament(teams)

        # If the winner has won before (its entry exists in the dictionary counts), we add a single count to it
        if ultimate_winner in counts:
            counts[ultimate_winner] += 1
        # Else if the winner has never won before, we declare an entry into the dictionary and a single win count number to it.
        else:
            counts[ultimate_winner] = 1

    # DONE: Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")

# DONE - CALCULATES WINNING PROBABILITY AND RETURN TRUE (FOR SIMULATE_ROUND) IF THE FIRST TEAM IS THE WINNER
# The simulate_game function accepts two teams as inputs (recall that each team is a dictionary containing the team name and the team’s rating), and simulates a game between them.
# If the first team wins, the function returns True; otherwise, the function returns False.


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability

# DONE - DESIGNING UP THE MATCH-UP BETWEEN TWO TEAMS AND RETURNS THE ACTUAL WINNER
# The simulate_round function accepts a list of teams (in a variable called teams) as input, and simulates games between each pair of teams.
# The function then returns a list of all of the teams that won the round.


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners

# DONE


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO
    # 1. This function should accept as input a list of teams and should repeatedly simulate rounds until you’re left with one team.
    # 2. You can call the simulate_round function, which simulates a single round, accepting a list of teams as input and returning a list of all of the winners.
        # Recall that if x is a list, you can use len(x) to determine the length of the list.
        # You should not assume the number of teams in the tournament, but you may assume it will be a power of 2.
    while len(teams) > 1:
        teams = simulate_round(teams)

    return teams[0]['team']


# END
if __name__ == "__main__":
    main()
