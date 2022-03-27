#include <cs50.h>

#include <stdio.h>

#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
#define MAX_NAME 50

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct {
  char name[MAX_NAME];
  int votes;
  bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count = -1;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
bool equalElements(int eleitor);

int main(int argc, string argv[]) {
  // Check for invalid usage
  if (argc < 2) {
    printf("Usage: runoff1 FILE\n");
    return 1;
  }

  FILE * fp = NULL;
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Error: I can't open '%s'.\n", argv[1]);
    return 1;
  }

  // read number of candidates
  fscanf(fp, "%i", & candidate_count);
  if (candidate_count > MAX_CANDIDATES) {
    printf("Error: maximum number of candidates is %i\n", MAX_CANDIDATES);
    return 2;
  }

  // populate array of candidates
  for (int i = 0; i < candidate_count; i++) {
    fscanf(fp, "%s", candidates[i].name);
    candidates[i].votes = 0;
    candidates[i].eliminated = false;
  }

  fscanf(fp, "%i", & voter_count);
  if (voter_count == -1) {
    printf("Error: file with wrong parameters\n");
    return 3;
  }
  if (voter_count > MAX_VOTERS) {
    printf("Maximum number of voters is %i\n", MAX_VOTERS);
    return 3;
  }

  // Keep querying for votes
  for (int i = 0; i < voter_count; i++) {

    // Query for each rank
    for (int j = 0; j < candidate_count; j++) {
      char name[MAX_NAME];
      fscanf(fp, "%s", name);

      // Record vote, unless it's invalid
      if (!vote(i, j, name)) {
        printf("Invalid vote.\n");
        return 4;
      }
    }
    //
    if (equalElements(i)) {
      printf("Invalid vote.\n");
      return 4;
    }
  }

  while (true) {
    // Calculate votes given remaining candidates
    tabulate();

    // Check if election has been won
    bool won = print_winner();
    if (won) {
      break;
    }

    // Eliminate last-place candidates
    int min = find_min();
    bool tie = is_tie(min);

    // If tie, everyone wins
    if (tie) {
      for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated) {
          printf("%s\n", candidates[i].name);
        }
      }
      break;
    }

    // Eliminate anyone with minimum number of votes
    eliminate(min);

    // Reset vote counts back to zero
    for (int i = 0; i < candidate_count; i++) {
      candidates[i].votes = 0;
    }
  }
  return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name) {
  // TODO
  for (int i = 0; i < candidate_count; i++) {
    if (strcmp(name, candidates[i].name) == 0) {
      preferences[voter][rank] = i;
      return true;
    }
  }
  return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void) {
  // TODO
  for (int i = 0; i < voter_count; i++) {
    for (int k = 0; k < candidate_count; k++) {
      if (!candidates[preferences[i][k]].eliminated) {
        candidates[preferences[i][k]].votes += 1;
        break;
      }
    }
  }
  return;
}

// Print the winner of the election, if there is one
bool print_winner(void) {
  // TODO
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes > voter_count / 2) {
      printf("%s\n", candidates[i].name);
      return true;
    }
  }
  return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void) {
  // TODO
  int indexMenorVotos = 0;
  for (int i = 1; i < candidate_count; i++) {
    if (candidates[i].votes < candidates[indexMenorVotos].votes) {
      indexMenorVotos = i;
    }
  }
  return candidates[indexMenorVotos].votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min) {
  // TODO
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes != min) {
      return false;
    }
  }
  return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min) {
  // TODO
  for (int i = 0; i < candidate_count; i++) {
    if (candidates[i].votes == min) {
      candidates[i].eliminated = true;
    }
  }
  return;
}

//Compara todos votos de um eleitor para vcer se ele votou em uma mesma pessoa 2+ vezes
bool equalElements(int eleitor) {

  for (int i = 0; i < candidate_count; i++) {
    for (int k = i + 1; k < candidate_count; k++) {
      if (preferences[eleitor][i] == preferences[eleitor][k]) {
        return true;
      }
    }
  }
  return false;
}
