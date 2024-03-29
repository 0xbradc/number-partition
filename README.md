# Number Partition Project

## About
This was created by Brad Campbell and Edward Dan in the spring of 2022. The program implements six different approaches to finding the best answer of the number partition problem given a list of integers.

## Limits
These algorithms were designed to find the best answer in an efficient time. They run in a reasonable amount time (under a few minutes) on large list inputs (billions of nodes/edges).

## Approach
This project made use of two approaches to partitions: binary and prepartitioned. 

The binary approach is simply sorting each element into either the "zero" set or the "one" set. Additionally, three algorithms were utilized: repeated random, hill climbing, and simulated annealing. To track progress, the Karmarkar-Karp algorithm was used in intermediate steps.

The prepartitioned approach involved random sorting into multiple different "buckets" and combining those buckets optimally until the best partition arrangement was found.

## More Information
For more information on the project, please contact me at bfcampbell@college.harvard.edu.
