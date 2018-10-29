# CellularAutomaton
Cellular Automaton Project - A C++ base implementing the Qt library for the visual interface

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
