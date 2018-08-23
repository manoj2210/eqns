# EQNS

### A GUI application with GTK+ and C language compatible in all desktop environments.

This repo helps us in finding the roots of polynomial equations with the time complexity of O(n^2) using Durand Kerner's Method. This also helps in solving the system of linear equations of 2 and 3 unknowns using the determinant approach.

## Roots of Polynomial Equation:
   Complex Roots of the Polynomial Equation are found using the [Durand Kerner's method](https://en.wikipedia.org/wiki/Durand%E2%80%93Kerner_method)

Currently `n`, degree of the polynomial equation is set to 10.
You can change that by changing the macro at 10th line,
```C
#define MAX_ROOT=10
```
## Solving System of linear equations of two and three unknowns:
The system of equations are solved using the determinant uproach depending on the value of Delta.



## Installation

Requires GTK+,

1. [Windows](https://www.gtk.org/docs/installations/windows/)
2. [Linux](https://www.gtk.org/docs/installations/linux/)
3. [MacOS](https://www.gtk.org/docs/installations/macos/)

```bash
git clone https://github.com/manoj2210/eqns.git
cd eqns
cc `pkg-config --cflags gtk+-3.0` main.c -o main `pkg-config --libs gtk+-3.0`
./main
```

## Usage

> 1. You can give inputs with respect to left hand and right hand side.
> 2. Infinitely many solution, No solution cases are handled in the program.
> 3. Use ^ symbol for powers.

### Example
>4x^2+5x=3

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License
[MIT](https://choosealicense.com/licenses/mit/)