#ifndef SANDPILES_H
#define SANDPILES_H

void sandpiles_sum(int grid1[3][3], int grid2[3][3]);
int is_stable(int grid[3][3]);
void topple(int grid[3][3]);
void print_grid_public(int grid[3][3]); // New public function

#endif /* SANDPILES_H */