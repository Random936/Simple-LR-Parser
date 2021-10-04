

```
E' -> E
E -> E + T
E -> E - T
E -> T
T -> T * F
T -> T / F
T -> F
F -> id
```




| Goto        | Item Set                                         | State | Extended                                                     |
| ----------- | ------------------------------------------------ | ----- | ------------------------------------------------------------ |
|             | E' -> . E                                        | 0     | E' -> . E<br/>E -> .  E + T<br/>E -> . E - T<br/>E -> . T<br/>T -> . T * F<br/>T -> . T / F<br/>T -> . F<br/>F -> . id |
| goto(0, E)  | E' -> E .<br/>E -> E . + T<br />E -> E . - T     | 1     |                                                              |
| goto(0, T)  | E -> T .<br />T -> T . * F<br />T -> T . / F     | 2     |                                                              |
| goto(0, F)  | T -> F .                                         | 3     |                                                              |
| goto(0, id) | F -> id .                                        | 4     |                                                              |
| goto(1, +)  | E -> E + . T                                     | 5     | E -> E + . T<br />T -> . T * F<br/>T -> . T / F<br/>T -> . F<br/>F -> . id |
| goto(1, -)  | E -> E - . T                                     | 6     | E -> E - . T<br />T -> . T * F<br/>T -> . T / F<br/>T -> . F<br/>F -> . id |
| goto(2, *)  | T -> T * . F                                     | 7     | T -> T * . F<br />F -> . id                                  |
| goto(2, /)  | T -> T / . F                                     | 8     | T -> T / . F<br />F -> . id                                  |
| goto(5, T)  | E -> E + T .<br />T -> T . * F<br />T -> T . / F | 9     |                                                              |
| goto(5, F)  | T -> F .                                         | 3     |                                                              |
| goto(5, id) | F -> id .                                        | 4     |                                                              |
| goto(6, T)  | E -> E - T .<br />T -> T . * F<br />T -> T . / F | 10    |                                                              |
| goto(6, F)  | T -> F .                                         | 3     |                                                              |
| goto(6, id) | F -> id .                                        | 4     |                                                              |
| goto(7, F)  | T -> T * F .                                     | 11    |                                                              |
| goto(7, id) | F -> id .                                        | 4     |                                                              |
| goto(8, F)  | T -> T / F .                                     | 12    |                                                              |
| goto(8, id) | F -> id .                                        | 4     |                                                              |
| goto(9, *)  | T -> T * . F                                     | 7     | T -> T * . F<br />F -> . id                                  |
| goto(9, /)  | T -> T / . F                                     | 8     | T -> T / . F<br />F -> . id                                  |
| goto(10, *) | T -> T * . F                                     | 7     | T -> T * . F<br />F -> . id                                  |
| goto(10, /) | T -> T / . F                                     | 8     | T -> T / . F<br />F -> . id                                  |



# Parse Table

|      | +    | -    | *    | /    | id   | $    | E    | T    | F    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 0    |      |      |      |      | s4   |      | 1    | 2    | 3    |
| 1    | s5   | s6   |      |      |      | acc  |      |      |      |
| 2    | r3   | r3   | s7   | s8   |      | r3   |      |      |      |
| 3    | r6   | r6   | r6   | r6   |      | r6   |      |      |      |
| 4    | r7   | r7   | r7   | r7   |      | r7   |      |      |      |
| 5    |      |      |      |      | s4   |      |      | 9    | 3    |
| 6    |      |      |      |      | s4   |      |      | 10   | 3    |
| 7    |      |      |      |      | s4   |      |      |      | 11   |
| 8    |      |      |      |      | s4   |      |      |      | 12   |
| 9    | r1   | r1   | s7   | s8   |      | r1   |      |      |      |
| 10   | r2   | r2   | s7   | s8   |      | r2   |      |      |      |
| 11   | r4   | r4   | r4   | r4   |      | r4   |      |      |      |
| 12   | r5   | r5   | r5   | r5   |      | r5   |      |      |      |

