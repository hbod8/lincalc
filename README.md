# lincalc
A simple calculator for performing operations on matricies.

## Initial goals:
- Create a structure for reading matricies from csv files.
- Display matrix structures in the command line.
- Create a way to pivot on a given position.

## Structure:

The code base will be stored in src/ and all commands given to lincalc will be in separate c files.

## Basic use cases:

**Title:** User loads a matrix from a csv file
**Actors:** user, lincalc
**Primary Actor:** user
**Preconditions:** lincalc is installed with all the nessicary dependencies.
**Trigger:** users runs lincalc
**Success condition:** User loads the csv file into lincalc.
**Alternate flows:** The file doesn't exist. The file is incorrectly formatted.

1. user specifies that they wish to load a file and the location of the csv.
2.a1. The file doesn't exist and lincalc displays an error.
2.a2. The file is formatted incorrectly and lincalc display a helpful error.
2. lincalc loads the csv file.

**Title:** User displays a matrix on the command line.
**Actors:** user, lincalc
**Primary Actor:** user
**Preconditions:** lincalc is installed with all the nessicary dependencies.
**Trigger:** users runs lincalc
**Success condition:** User displays a matrix that is loaded into lincalc.
**Alternate flows:** The matrix doesnt exist.

1. user specifies that a matrix should be displayed and what the matrix name is.
2.a1. the matrix doesn't exist and lincalc displays an error.
2. lincalc prints the matrix in the command line.

**Title:** User pivots a maxtix at a specified position.
**Actors:** user, lincalc
**Primary Actor:** user
**Preconditions:** lincalc is installed with all the nessicary dependencies. A matrix is loaded into lincalc.
**Trigger:** users runs lincalc and loads a matrix
**Success condition:** The matrix is pivoted around the specified point.
**Alternate flows:** The matrix doesnt exist. The pivot is out of bounds.

1. user specifies that a matrix and the row and column of the pivot.
2.a1. the matrix doesn't exist and lincalc displays an error.
2.a2. the position is out of bounds and lincalc displays an error.
2. lincalc prints the matrix in the command line.