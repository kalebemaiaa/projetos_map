#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// max number of candidates
#define MAX 9
#define MAX_NAME 50

// candidates have name and vote count
typedef struct
{
    char name[MAX_NAME];
    int votes;
}
candidate;

candidate candidates[MAX];

// number of candidates
int candidate_count;

// function prototypes
bool vote(string name);
void print_winner(void);


int main(int argc, string argv[])
{
  // Check for invalid usage
  if (argc < 2)
  {
      printf("Usage: plurality FILE\n");
      return 1;
  }

  FILE* fp = NULL;
  fp = fopen(argv[1], "r");
  if (fp == NULL)
  {
    printf("Error: I can't open '%s'.\n", argv[1]);
    return 1;
  }

  // read number of candidates
  fscanf(fp, "%i", &candidate_count);
  if (candidate_count > MAX)
  {
    printf("Error: maximum number of candidates is %i\n", MAX);
    return 2;
  }

    // populate array of candidates
  for (int i = 0; i < candidate_count; i++)
  {
    fscanf(fp, "%s", candidates[i].name);
    candidates[i].votes = 0;
  }

  int voter_count;
  fscanf(fp, "%i", &voter_count);

  // loop over all voters
  for (int i = 0; i < voter_count; i++)
  {
    char name[MAX_NAME];
    fscanf(fp, "%s", name);

    // Check for invalid vote
    if (!vote(name))
    {
      printf("Error: invalid file.\n");
      return 2;
    }
  }
  print_winner();

  // close the file
  fclose(fp);
}

// Update vote totals given a new vote
bool vote(string name)
{
  for(int i = 0; i < candidate_count; i++)
  {
    if(strcmp(candidates[i].name, name) == 0)
    {
      candidates[i].votes+=1;
      return true;
    }
  }
  return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
  int winner = 0;
  for(int i = 1; i < candidate_count; i++)
  {
    if(candidates[i].votes>candidates[winner].votes)
    {
      winner = i;
    }
  }
  printf("%s\n",candidates[winner].name);
  for(int i = 1;i<candidate_count;i++)
  {
    if(i==winner)
    {
      continue;
    }
    if(candidates[i].votes==candidates[winner].votes)
    {
      printf("%s\n",candidates[i].name);
    }
  }
  return;
}
