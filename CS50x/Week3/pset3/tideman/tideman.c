#include <cs50.h>
#include <stdio.h>
// Adding <string.h> to template. Usage: `strcmp`
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// Declare the would_create_cycle function
bool would_create_cycle(int winner, int loser);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Iterate through list of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If name of candidate at current index matches name of voted candidate
        if (strcmp(candidates[i], name) == 0)
        {
            //  Update ranks array with the index of the candidate
            ranks[rank] = i;

            // Return true to indicate that the vote is valid
            return true;
        }
    }

    // Return false if name of voted candidate is not found in the list of candidates
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Iterate through the ranks array
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare each candidate to the candidates ranked after it
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Increment the preference count in the preferences array for the pair
            // of candidates where the candidate at the current index is preferred
            // over the candidate at the next index
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate through the preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If candidate at current index is preferred over candidate at next index
            if (preferences[i][j] > preferences[j][i])
            {
                // Add the pair to the pairs array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // If candidate at next index is preferred over candidate at current index
            else if (preferences[i][j] < preferences[j][i])
            {
                // Add the pair to the pairs array
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Iterate through the pairs array
    for (int i = 0; i < pair_count - 1; i++)
    {
        // Initialize maximum strength of victory and the index of the pair with the max strength
        int max_strength = preferences[pairs[i].winner][pairs[i].loser];

        int max_index = i;

        // Iterate through remaining pairs
        for (int j = i + 1; j < pair_count; j++)
        {
            // Get victory's strength of current pair
            int strength = preferences[pairs[j].winner][pairs[j].loser];

            // If victory's strength of current pair is greater than max strength
            if (strength > max_strength)
            {
                // Update max victory's strength and index of pair with max strength
                max_strength = strength;
                max_index = j;
            }
        }

        // If pair with max strength is not already at the front of the array
        if (max_index != i)
        {
            // Swap the positions of the pair with max strength and the pair
            // current index
            pair temp = pairs[i];
            pairs[i] = pairs[max_index];
            pairs[max_index] = temp;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Iterarate through the pairs array
    for (int i = 0; i < pair_count; i++)
    {
        // Get the winner and loser of the current pair
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        // IF the reverse of the current pair is not already in the graph
        // (i.e IF loser is not already locked in over winner)

        // Check if adding current pair to graph would create a cycle
        bool cycle = would_create_cycle(winner, loser);

        // If the pair would not create a cycle, add it to the locked graph
        if (!cycle)
        {
            // ...Add current pair to the graph
            locked[winner][loser] = true;
        }
        // If the pair would create a cycle, skip final pair and continue the loop
        else
        {
            continue;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Iterate through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Initialize a flag to check if candidate has any incoming edges
        bool has_edges = false;

        // Check if candidate has any incoming edges
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                has_edges = true;
                break;
            }
        }

        // If candidate has no incoming edges, cnadidate is source of graph
        if (!has_edges)
        {
            // Print name of candidate
            printf("%s\n", candidates[i]);
            return;
        }
    }
}

// Check if adding the given pair to the locked graph would create a cycle
bool would_create_cycle(int winner, int loser)
{

    // Iterate through candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // If loser is locked in over current candidate
        if (locked[loser][i])
        {
            // Recursively check if adding current pair would create a cycle
            if (would_create_cycle(winner, i))
            {
                return true;
            }
            // If the loser has a locked-in edge to thee winner, there is a cycle
            else if (i == winner)
            {
                return true;
            }
        }
    }

    // If loser does not have any locked-in edges, adding new pair would not create cycle
    return false;
}