// Generates a random number with a range in the middle that is excluded.

int generateRandomNumber(int min, int max, int excludeMin, int excludeMax) {
  int num;

  // Seed the random number generator with the analog reading from pin A0
  randomSeed(analogRead(A0));

  // Generate random numbers until we find one that's not in the excluded range
  do {
    num = random(min, max + 1);
  } while (num >= excludeMin && num <= excludeMax);

  return num;
}
