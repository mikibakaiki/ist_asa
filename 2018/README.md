## Algorithm Analysis | 2 Semester 2017/2018 ##

* João Miguel Campos, 75785, LEIC-T


**Course:** Análise e Síntese de Algoritmos (ASA) | Algorithm Analysis

**Course Link:** https://fenix.tecnico.ulisboa.pt/disciplinas/ASA10111326/2017-2018/2-semestre


### 1st Project ###

This project is about finding the SCC on a given graph and if there are any edges going from one SCC to another SCC.
I used [Tarjan's Algorithm](https://en.wikipedia.org/wiki/Tarjan%27s_strongly_connected_components_algorithm) to find these SCC's.

**Grades:**
* Code test and execution: 16 / 16;
* Code explanation, theorethical and practical analysis : 3.5 / 4;
* Total: 19.5 / 20;



### 2nd Project ###

This project is about generating a [Minimum Spanning Tree](https://en.wikipedia.org/wiki/Minimum_spanning_tree). We used [Kruskal's Algorithm](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm).

We had to decide which infrastructure a city should build - road or airport - in order to have all citys connected, with the minimum cost possible. If a city has an airport, it is connected to all others cities that also have airports (we create an extra vertex that we can call the vertex "SKY" and is shared by every city that has an airport). Otherwise, the cities must be connected with roads. If building a road or an airport generates the same cost, roads are prioritized.


**Grades:**
* Code test and execution: 16 / 16;
* Code explanation, theorethical and practical analysis : 3.5 / 4;
* Total: 19.5 / 20;

[**Inspiration**](https://github.com/erkekin/Kruskal)



### Some gdb Commands to Remember ###

| Command        | Meaning         
| :-------------: |:-------------:|
| `gdb ./<file_to_execute_>`      | run gdb with the program you want to test |
| `(gdb)b line_number`      | insert a `b`reak in given `line_number`     |
| `(gdb)r < path/to/some/testfile.txt` | `r`un the program with `testfile.txt`'s input     |
| `(gdb)n` | `n`ext command to execute on program     |
| `(gdb)p some_variable` | `p`rint `some_variable`'s value    |
|`Ctrl + x + a`|enter TUI mode :)|


**Disclaimer:**
This repository, and every other ist_COURSE repos on GitHub correspond to school projects from the respective COURSE. The code on this repo is intended for educational purposes. I do not take any responsibility nor liability over any code faults, inconsistency or anything else. If you intend on copying most or parts of the code for your school projects, keep in mind that this repo is public, and that your professor might search the web for similar project solutions and choose to fail you for copying.



## Have fun coding! :)
