#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
// TOTAL COUNT OF VOTES
// Rows have the votes of a given candidate against the others:
// preferences[candidateIdx][competitorIdx]
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j DEFINES THE SOURCE/WINNER
// the biggest pair difference locks the relation with the candidate:
// if [1][2] is locked, [3][1] cannot be, as [4][1], [5][1]...
// THE CANDIDATE WITH HIGHEST QUANTITY OF LOCKS WINS
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
  int winner;
  int loser;
} pair;

// Array of candidates DEFINES ORDER OF CANDIDATES BY INDEX
string candidates[MAX];
// pairs of winner/losers
// biggest pair locks the winner
pair pairs[MAX * (MAX - 1) / 2];

// for loop's sake
int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: tideman [candidate ...]\n");
    return 1;
  }

  // Populate array of candidates
  candidate_count = argc - 1;
  if (candidate_count > MAX) {
    printf("Maximum number of candidates is %i\n", MAX);
    return 2;
  }
  for (int i = 0; i < candidate_count; i++) {
    candidates[i] = argv[i + 1];
  }

  // Clear graph of locked in pairs
  for (int i = 0; i < candidate_count; i++) {
    for (int j = 0; j < candidate_count; j++) {
      locked[i][j] = false;
    }
  }

  pair_count = 0;
  int voter_count = get_int("Number of voters: ");

  // Query for votes
  for (int i = 0; i < voter_count; i++) {
    // ranks[i] is voter's ith preference
    int ranks[candidate_count];

    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      string name = get_string("Rank %i: ", j + 1);

      if (!vote(j, name, ranks)) {
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
bool vote(int rank, string name, int ranks[]) {
  if (rank > candidate_count) {
    return false;
  }

  for (int candidateIdx = 0; candidateIdx < candidate_count; candidateIdx++) {
    if (strcmp(name, candidates[candidateIdx]) == 0) {
      ranks[rank] = candidateIdx;
      return true;
    }
  }
  return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) {
  for (int ranksIdx = 0; ranksIdx < candidate_count; ranksIdx++) {
    for (int comparisonIdx = ranksIdx + 1; comparisonIdx < candidate_count;
         comparisonIdx++) {
      int winnerIdx = ranks[ranksIdx];
      int loserIdx = ranks[comparisonIdx];
      preferences[winnerIdx][loserIdx] += 1;
    }
  }
  return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
  for (int rowIdx = 0; rowIdx < candidate_count; rowIdx++) {
    for (int columnIdx = 0; columnIdx < candidate_count; columnIdx++) {
      int candidate1votes = preferences[rowIdx][columnIdx];
      int candidate2votes = preferences[columnIdx][rowIdx];

      if (rowIdx != columnIdx && candidate1votes > candidate2votes &&
          rowIdx > columnIdx) {
        pairs[pair_count].winner = rowIdx;
        pairs[pair_count].loser = columnIdx;
        pair_count += 1;
      } else if (rowIdx != columnIdx && candidate2votes > candidate1votes &&
                 rowIdx > columnIdx) {
        pairs[pair_count].winner = columnIdx;
        pairs[pair_count].loser = rowIdx;
        pair_count += 1;
      }
    }
  }
  return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
  for (int leftPointer = 0; leftPointer < pair_count; leftPointer++) {
    int leftPointerVoteDifference =
        preferences[pairs[leftPointer].winner][pairs[leftPointer].loser] -
        preferences[pairs[leftPointer].loser][pairs[leftPointer].winner];

    for (int rightPointer = leftPointer + 1; rightPointer < pair_count;
         rightPointer++) {
      int rightPointerPairVoteDifference =
          preferences[pairs[rightPointer].winner][pairs[rightPointer].loser] -
          preferences[pairs[rightPointer].loser][pairs[rightPointer].winner];

      if (rightPointerPairVoteDifference > leftPointerVoteDifference) {
        pair temp;
        temp.winner = pairs[leftPointer].winner;
        temp.loser = pairs[leftPointer].loser;
        pairs[leftPointer].winner = pairs[rightPointer].winner;
        pairs[leftPointer].loser = pairs[rightPointer].loser;
        pairs[rightPointer].winner = temp.winner;
        pairs[rightPointer].loser = temp.loser;
      }
    }
  }
  return;
}

// checks if pair to be locked results in  cycle
bool isCycle(int winnerToLock, int loserToLock) {
  // if the pair's loser is locked as winner of the winner before, it is cycle
  if (locked[loserToLock][winnerToLock] == true) {
    return true;
  }

  for (int otherLoserIdx = 0; otherLoserIdx < candidate_count;
       otherLoserIdx++) {
    // if the loser wins in another lock (locked[loser][i]) and
    // the recursion of the winner with the candidate
    //(isCycle(winner, i)) returns true,
    // it is a cycle.
    if (locked[loserToLock][otherLoserIdx] &&
        isCycle(winnerToLock, otherLoserIdx)) {
      return true;
    }
  }

  // if not, it is not a cycle
  return false;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
  for (int i = 0; i < pair_count; i++) {
    if (!isCycle(pairs[i].winner, pairs[i].loser)) {
      locked[pairs[i].winner][pairs[i].loser] = true;
    }
  }

  return;
}
// Print the winner of the election
void print_winner(void) {
  int winner;

  // iterate the locked matrix to search for a winner
  // the winner wont have been locked as a loser
  for (winner = 0; winner < candidate_count; winner++) {
    int isLoser = 0;
    for (int rightPointer = 0; rightPointer < candidate_count; rightPointer++) {
      if (locked[rightPointer][winner]) {
        isLoser = 1;
      }
    }

    if (!isLoser) {
      printf("%s\n", candidates[winner]);
      return;
    }
  }

  printf("Ops. There are no winners.\n");

  return;
}
