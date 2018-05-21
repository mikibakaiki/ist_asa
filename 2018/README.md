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

This project was about image segmentation. Given a matrix of pixels, we had to decide which ones belonged to the background (_C_) and which ones were part of the plane of view (_P_). For this, 2 extra vertices were created, _S_ and _t_, indicating a _Source_ and a _sink_ (why is it t though?). So, it's a Max-flow-Min-cut problem, and we wanted to find the Maximum Flow of the network, using [Edmonds-Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm). Given this [theorem](https://en.wikipedia.org/wiki/Max-flow_min-cut_theorem) when you find the Maximum Flow, you also have found out the Minimum Cut. And so, the vertices were categorized as _C_ if they were reachable from the Source (and thus belong to the set {_S_, _x_} where _x_ is the set of vertices reachable from _S_ on a _BFS_ - this set defines the Minimum Cut) and the others were labeled as _P_.


**Grades:**
* Code test and execution: 16 / 16;
* Code explanation, theorethical and practical analysis : 4 / 4;
* Total: 20 / 20;




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
