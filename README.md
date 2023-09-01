# Compiling and Running the estimatecron Program

This guide will walk you through the process of compiling and running the `estimatecron` program using the `make` command. Additionally, it will cover the steps from cloning the repository on GitHub to executing the program.

## Prerequisites

Before you start, ensure you have the following:

1. Git installed on your system.
2. A C compiler that supports the C11 standard, such as GCC.
3. Basic familiarity with using the command line interface.

## Cloning the Repository

1. **Clone the Repository:**

   Open a terminal window and navigate to the directory where you want to clone the repository. Then, run the following command to clone the repository:

   ```sh
   git clone https://github.com/your-username/estimatecron.git
   ```

   Replace `your-username` with your GitHub username.

2. **Navigate to Repository:**

   Move into the cloned repository's directory:

   ```sh
   cd estimatecron
   ```

## Compilation and Running

1. **Compile the Program:**

   In the repository directory, use the `make` command to compile the `estimatecron` program. The `Makefile` provided simplifies the compilation process and ensures that dependencies are handled correctly:

   ```sh
   make
   ```

   This will generate an executable file named `estimatecron`.

2. **Run the Program:**

   Execute the `estimatecron` program using the following command:

   ```sh
   ./estimatecron
   ```

   The program will run and provide you with estimates for the execution time of cron jobs using simulations.

## Cleaning Up

If you wish to remove the compiled executable and object files, you can use the following command:

```sh
make clean
```

## Troubleshooting

- If you encounter any compilation errors, make sure you have the prerequisites installed and that the source code files are in the correct directory.

- If you have trouble running the program, ensure you are in the `estimatecron` directory and that the `estimatecron` executable is present.

## Summary

By following these steps, you have successfully cloned the repository from GitHub, compiled the `estimatecron` program using the `make` command, and executed the program to estimate cron job execution times.
