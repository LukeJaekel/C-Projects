#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Looping through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks whether candidate names match to input
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Updating preferences array
            preferences[voter][rank] = i;
            return true;
        }
    }
    // Otherwise, it returns false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Looping through voters
    for (int i = 0; i < voter_count; i++)
    {
        // AND looping through candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // Checks whether each candidate has been eliminated
            if (candidates[preferences[i][j]].eliminated == false)
            {
                // Candidates each recieve a point if NOT eliminated
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Looping through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks each candidates total score and whether it's greater than half of vote count
        if (candidates[i].votes > (voter_count / 2))
        {
            // If true, then the candidate's name will be printed
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // Otherwise, it returns false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Declaring a minimum count variable
    int min = voter_count;

    // Looping through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks whether a candidate has not been eliminated AND a candidate's votes is less than the minimum
        if ((candidates[i].eliminated == false) && (candidates[i].votes < min))
        {
            // If true, then the minimum count becomes the new candidate vote count
            min = candidates[i].votes;
        }
    }
    // Otherwise, it returns the minimum count (i.e. voter_count)
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Declaring variable to represent no. of candidates still running in election
    int eliminate = 0;

    // Declaring variable to represent no. of candidates equals to minimum count
    int count = 0;

    // Looping through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If a candidate is not eliminated
        if (!candidates[i].eliminated)
        {
            // Eliminiate variable increments by 1
            eliminate++;
        }
        // If a candidates votes is equal to the minimum count
        if (candidates[i].votes == min)
        {
            // Count variable increments by 1
            count++;
        }
    }
    // Checks whether they are equal (i.e a tie)
    if (eliminate == count)
    {
        // If true, the function will return true
        return true;
    }
    // Otherwise, the function will return false
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Looping through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks which candidate's vote is the lowest
        if (candidates[i].votes == min)
        {
            // If true, that candidate will be eliminated
            candidates[i].eliminated = true;
        }
    }
    return;
}
