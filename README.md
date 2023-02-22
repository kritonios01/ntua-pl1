# ntua-pl1
Exercise repository for Programming Languages 1, ECE NTUA course.
This is a mandatory 6th semester course for anyone who chooses to follow the Computer Software flow in the Electrical and Computer Engineering School of NTUA.

### Participants
* Iordanidis Kriton
* Emmanouil Pantelis

We took this course during the academic year 2021-2022. That year only 2 exercises were given, each of which consisted of writing two tantamount programs, one in C++ and one in SML of New Jersey. We used C++ 11 and SMLNJ v110.99.2. Example input files can be found inside each exercise's folder

### Exercise 1
A text, encrypted according to [ROTN cipher](https://en.wikipedia.org/wiki/Caesar_cipher), is given as input and the program decrypts it. Note that the number of positions the alphabet is rotated is unknown, so we make use of an entropy function in order to decrypt.
#### 	For C++
Compile the source code and run:
```shell
$ ./<binary_name> input.txt
```
#### For SMLNJ
Run the sml binary in your shell and then type:
```shell
- decrypt "input.txt";
```

### Exercise 2
We are given N numbered cities and M paths which connect (some of) those cities. For each path we are also given the amount of gas required to make it through it. Let L be the reservoir capacity of a car. The program finds the minimum possible capacity L so that the car can be driven from any city to any other city. The input file must be in the following format:

|input.txt|
|---------|
|N M      |
|A1 B1 W1 |
|A2 B2 W2 |
| ....    |
|Am Bm Wm |

> In the first line we give the number of cities (N) and number of paths(M). Then, for M lines we define each path: Ax is the starting city, Bx is the ending city and Wx is the amount of gas required from start to finish.

#### 	For C++
Compile the source code and run:
```shell
$ ./<binary_name> input.txt
```
#### For SMLNJ
Run the sml binary in your shell and then type:
```shell
- min_fill "input.txt";
```

