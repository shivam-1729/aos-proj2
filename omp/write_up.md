### Team members
1. Gaurav Dadlaney (gdadlaney3@gatech.edu)
2. Shivam Saxena ()

## Intro
- An introduction that provides an overview of what you did (do not assume the reader has already read this assignment description).

### Project break-up
    An explanation of how the work was divided between the team members (i.e., who did what)
    
## Barrier Algo
    A description of the barrier algorithms that you implemented. You do not need to go into as much implementation detail (with pseudocode and so forth) as the MCS paper did. However, you should include a good high-level description of each algorithm. You should not simply say that you implement algorithm X from the paper and refer the reader to the MCS paper for details.

## Experiments
### Experiments run, results & analysis
#### Open MP
1. Increasing number of threads exponentially: 10, 100, 1000
    - The amount of time taken by the threads to reset the barrier increases more than expontentially
    ```
    real    0m0.007s
    user    0m0.001s
    sys     0m0.010s

    real    0m25.286s
    user    0m23.414s
    sys     0m0.034s

    real    3m28.392s
    user    3m25.344s
    sys     0m0.280s
    ```

    An explanation of the experiments, including what experiments you ran, your experimental set-up, and your experimental methodology. Give thorough details. Do not assume the reader has already read this assignment description.
    Your experimental results. DO present your data using graphs. DO NOT use tables of numbers when a graph would be better (Hint: a graph is usually better). DO NOT include all your raw data in the write-up. Compare both your OpenMP barriers. Compare both your MPI barriers. Present the results for your MPI-OpenMP barrier.
    An analysis of your experimental results. You should explain why you got the results that you did (think about the algorithm details and the architecture of the machine on which you experimented). Explain any trends or interesting phenomena. If you see anything in your results that you did not expect, explain what you did expect to see and why your actual results are different. There should be at least a couple of interesting points per experiment. The key is not to explain only the what of your results, but the how and why as well.


## Conclusion
