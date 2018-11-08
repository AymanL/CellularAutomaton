# CellularAutomaton Project
Cellular Automaton Project - A C++ base implementing the Qt library for the visual interface

The application is used to simulate the behavior of cellular automaton and the evolution of cells. The algorithmic part is coded in the object-oriented programming language C++ and the interface designed with the Qt framework. The application can simulate the behavior of a basic 1 dimension state automatons (single row), Conway's Game of Life (grid filled with cells having 2 possibles states: dead and alive) and a forest fire(grid filled with cells having 4 possibles states: empty, tree, fire and ashes).

## Cellular Automaton Definition
> "A cellular automaton is a collection of "colored" cells on a grid of specified shape that evolves through a number of discrete time steps according to a set of rules based on the states of neighboring cells. The rules are then applied iteratively for as many time steps as desired."

![automatonExample](http://mathworld.wolfram.com/images/eps-gif/ElementaryCARule030_700.gif)

*Source: [Wolfram Math World](http://mathworld.wolfram.com/CellularAutomaton.html)*


The project uses multiple objects split into multiple files:

## Autocell
Defines the one dimension automaton Simulator interface.

## Autocell2D
Defines Conway's game of life Simulator interface.

## Autofeu
Defines a Forest Fire Simulator interface.

## Automaton
Defines generic automatons, specific automatons (one dimension, game of life and forest fire) and all of their methods and variables.

## Interface
Defines the main interface of the app.

## Main
Launches the app.

## Simulator
Uses an Automaton to simulate the evolution from a State to the next using the Automaton parameters.

## State
Defines a configuration of cells.

## XML_DOM
Defines data structurs and methods to save and load automaton configuration.

## Projet.pro
Qt project file.
