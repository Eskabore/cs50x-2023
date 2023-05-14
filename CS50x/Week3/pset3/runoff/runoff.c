#include <cs50.h>
#include <stdio.h>

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
    // Check if voter index is within valid range
    if (voter >= MAX_VOTERS)
    {
        return false;
    }

    // Iterate through the candidates array
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        // If candidate's name matches given name, record vote
        if (candidates[i].name == name)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }

    // If candidate's name not found, return false
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Iterate through the preferences array
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate through the preferences of the current voter
        for (int j = 0; j <= MAX_CANDIDATES; j++)
        {
            // If current preference is not an eliminated candidate,
            // increment vote count
            if (!candidates[preferences[i][j]].eliminated)
            {
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
    // Iterate through the candidates array
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        // Calculate number of votes needed for winning
        int votes_needed = voter_count / 2;

        // Check if current candidate has more than half of the votes
        if (candidates[i].votes > votes_needed)
        {
            // If the candidate has more than half of the votes,
            // print candidate's name and return true
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    // If no candidate has more than half of the votes, return false
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Initialize min number of votes to the max possible value
    int min_votes = voter_count + 1;

    // Iterate through the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // If current candidate is not eliminated,
        // 'and' has fewer votes than current min,
        // update min number of votes
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }

    // Return min number of votes
    return min_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Initialize flag to true
    bool tie = true;

    // Iterate through the candidate array
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        // If current candidate is not eliminated
        // 'and' has more votes than min number of votes,
        // set flag to false and break loop
        if (!candidates[i].eliminated && candidates[i].votes > min)
        {
            tie = false;
            break;
        }
    }

    // If all remaining candidates have same number of votes, return true
    return tie;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Iterate through the candidates array
    for (int i = 0; i < MAX_CANDIDATES; i++)
    {
        // If the current candidate has less or same number of votes than min number,
        // eliminate candidate
        if (candidates[i].votes <= min)
        {
            candidates[i].eliminated = true;
        }
    }
}