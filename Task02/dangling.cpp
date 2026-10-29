// Compile for diagnostics only. Do not use the returned reference.
int& bad() { int local=42; return local; }
int main() { return 0; }
