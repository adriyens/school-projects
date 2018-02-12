# File: proj2.py
# Author: Adrianne Santinor
# Date: 11/30/2016
# Section: 22
# E-mail: santa1@umbc.edu
# Description: This program uses recursion to solve a maze game.
# Collaboration: I did not collaborate with anyone for this assignment.

# constants that correspond the index of a list to the position of a wall
RIGHT = 0
BOTTOM = 1
LEFT = 2
TOP = 3

# empty list that will be populated with the coordinates of the maze exit
FINISH = []

# takes in a file name from user input and creates a 3d list
# input: file name
# output: 3d list as the maze
def readMaze(fileName):
    openMaze = open(fileName)
    readMaze = openMaze.readlines()
    intList = []

    for lines in readMaze:
        nums = lines.split()
        intList.append(nums)

    # assigns the number of row and columns to a variable
    rows = int(intList[0][0])
    columns = int(intList[0][1])

    endRow = int(intList[1][0])
    endColumn = int(intList[1][1])
    # adds the coordinates of the "finish" in the form of a tuple
    FINISH.append((endRow, endColumn))
    
    # makes a new list of just the walls that make up the maze
    squares = intList[2:]
    
    mazeBoard = [[]]*rows
    currRow = 0
    
    # iterates through the squares list by the number of columns so that only 
    # that amount populates the row
    for i in range(0, len(squares) - columns + 1, columns):
        mazeBoard[currRow] = squares[i:i+columns]
        currRow += 1

    openMaze.close()

    return mazeBoard

# goes through the maze one square at a time if there is no wall and returns 
# a solution to the maze if there is one.
# input: maze board, starting row, starting column, empty list
# output: solution path (if there is one)
def searchMaze(board, sRow, sColumn, currentPath):
    CLOSED = "1"
    OPEN = "0"
    coordinates = (sRow, sColumn)
    goal = FINISH[0]

    currentPath.append(coordinates)

    # if the path reaches the exit, then return the solution path
    if coordinates == goal:
        print("Solution found!")
        return currentPath

    # makes sure that the coordinates are within the indices of the maze
    while sRow > 0 or sRow < len(board) - 1 or sColumn > 0 or sColumn < len(board[sRow]) - 1:
        # checks if there are walls on all four sides, and if they're open,
        # goes over one square at a time.
        if board[sRow][sColumn][RIGHT] == OPEN:
            return searchMaze(board, sRow, sColumn + 1, currentPath)
        elif board[sRow][sColumn][BOTTOM] == OPEN:
            return searchMaze(board, sRow + 1, sColumn, currentPath)
        elif board[sRow][sColumn][LEFT] == OPEN:
            return searchMaze(board, sRow - 1, sColumn, currentPath)
        elif board[sRow][sColumn][TOP] == OPEN:
            return searchMaze(board, sRow, sColumn - 1, currentPath)
        else: 
            return None
    
def main():

    maze = []
    solution = []

    print("Welcome to the Maze Solver!")
    mazeFile = input("Please enter the filename of the maze: ")
    
    maze = readMaze(mazeFile)
    goal = FINISH[0]

    startRow = int(input("Please enter the starting row: "))

    # validates that the integer user inputs is within the maze list indices
    while startRow < 0 or startRow > len(maze) - 1:
        startRow = int(input("Enter a number between 0 and " + str(len(maze) - 1) + " (inclusive): "))

    startColumn = int(input("Please enter the starting column: "))
    while startColumn < 0 or startColumn > len(maze[0]) - 1:
        startColumn = int(input("Enter a number between 0 and " + str(len(maze[0]) - 1) + " (inclusive): "))
    
    solution = searchMaze(maze, startRow, startColumn, solution)
    
    # if the solution path isn't empty then print the path
    if solution != None:
        # if the last coordinate isn't the finish, then print "No solution."
        if solution[-1] != goal:
            print("No solution.")
        else:
            for paths in solution:
                print(paths)
    # and if the list is empty, print "No solution."
    else:
        print("No solution.")

main()
