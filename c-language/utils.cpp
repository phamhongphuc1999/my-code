bool exists(int mask, int index)
{
  return (mask >> index) & 1;
}

int add(int mask, int x)
{
  int result = (1 << x) | mask;
  return result;
}

void subtract(int &mask, int x)
{
  mask &= ~(1 << x);
}