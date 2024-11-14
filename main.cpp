// main.cpp
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib> // For std::atoi
#include <chrono>  // For timing
#include <iomanip> // For std::setw and std::fixed
#include <vector>  // For std::vector
#include "Backend/Board.h"         // Include Board.h for chess board representation
#include "Backend/Type/Square.h"   // Include Square.h to use the Square enum
#include "SimplifiedMoveList.h"    // Include your SimplifiedMoveList class
#include "Backend/Type/Color.h"
#include "Engine.h"                // Include your Engine class

constexpr int maxDepth = 25; // Adjust as needed

// Function to convert a Square enum to its string representation (e.g., E2 -> "e2")
std::string squareToString(Square square) {
    return std::string(1, File(square)) + std::string(1, Rank(square));
}

// Function to display usage instructions
void printUsage(const std::string &programName) {
    std::cerr << "Usage: " << programName << " <depth>\n";
    std::cerr << "  <depth> : Positive integer specifying the search depth.\n";
    std::cerr << "Example:\n";
    std::cerr << "  " << programName << " 4\n";
}

// Function to display the algorithm options list
void displayAlgorithmOptions() {
    std::cout << "Choose an option:\n";
    std::cout << "1. Young Brothers Wait Concept (YBWC)\n";
    std::cout << "2. Principal Variation Search (PVS)\n";
    std::cout << "3. Parallel Alpha-Beta Nega\n";
    std::cout << "4. Run Performance Tests\n"; // Option 4 for testing
    std::cout << "5. Count Total Possible Move Sequences\n"; // Option 5 for move counting
    std::cout << "Enter your choice (1, 2, 3, 4, or 5): ";
}

// Function to run performance tests
void runPerformanceTests(int depth) {
    // Initialize the engine
    Engine engine;

    // Prompt the user for a FEN for testing
    std::string testFEN;
    while (true) {
        std::cout << "Enter the FEN string to use for performance tests (or press Enter to use the default test position): ";
        std::getline(std::cin, testFEN);

        if (testFEN.empty()) {
            // Use the default test position
            testFEN = "8/K7/7r/8/2k5/5bb1/8/8 b - - 0 1";
            std::cout << "Using default test position.\n";
        }

        try {
            // Initialize a test chess board
            StockDory::Board testBoard;
            testBoard.SetFEN(testFEN);
            break; // Successfully set FEN
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to set FEN: " << e.what() << "\n";
            std::cout << "Please enter a valid FEN string.\n";
        }
    }

    // After validating the FEN, set up the test board
    StockDory::Board testBoard;
    try {
        testBoard.SetFEN(testFEN);
    }
    catch (const std::exception& e) {
        // This should not happen as we have already validated the FEN
        std::cerr << "Unexpected error setting FEN: " << e.what() << "\n";
        return;
    }

    // Define the thread counts to test
    std::vector<int> threadCounts = {1, 2, 5, 10, 25, 32, 50}; // Adjust thread counts as needed

    // Define the algorithms to test
    enum Algorithm { YBWC_ALGO = 1, PVS_ALGO, PARALLEL_ALPHA_BETA_NEGA_ALGO };
    std::vector<Algorithm> algorithms = {YBWC_ALGO, PVS_ALGO, PARALLEL_ALPHA_BETA_NEGA_ALGO};

    // Define algorithm names for display
    std::vector<std::string> algorithmNames = {
        "Young Brothers Wait Concept (YBWC)",
        "Principal Variation Search (PVS)",
        "Parallel Alpha-Beta Nega"
    };

    // Header for the results table
    std::cout << "\nPerformance Testing Results:\n";
    std::cout << "--------------------------------------------------------------\n";
    std::cout << "| Algorithm                     | Threads | Time (s)          |\n";
    std::cout << "--------------------------------------------------------------\n";

    // Iterate through each algorithm
    for (size_t algoIdx = 0; algoIdx < algorithms.size(); ++algoIdx) {
        Algorithm algo = algorithms[algoIdx];
        std::string algoName = algorithmNames[algoIdx];

        // Iterate through each thread count
        for (const auto& threads : threadCounts) {
            // Set the number of threads in the engine
            engine.setNumThreads(threads);

            // Initialize a fresh chess board for each run to ensure consistency
            StockDory::Board runBoard;
            try {
                runBoard.SetFEN(testFEN);
            }
            catch (const std::exception& e) {
                std::cerr << "Error setting FEN for performance test: " << e.what() << "\n";
                continue; // Skip this run
            }

            // Start timing
            auto start = std::chrono::high_resolution_clock::now();

            // Execute the chosen algorithm
            if (algo == YBWC_ALGO) {
                // Execute YBWC
                auto result = engine.YBWC<White, maxDepth>(
                    runBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );
                // You can optionally store or verify the result
            }
            else if (algo == PVS_ALGO) {
                // Execute PVS
                auto result = engine.PVS<White, maxDepth>(
                    runBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );
                // You can optionally store or verify the result
            }
            else if (algo == PARALLEL_ALPHA_BETA_NEGA_ALGO) {
                // Execute Parallel Alpha-Beta Nega
                auto result = engine.parallelAlphaBetaNega<White, maxDepth>(
                    runBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );
                // You can optionally store or verify the result
            }

            // End timing
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;

            // Output the result in the table
            std::cout << "| " << std::left << std::setw(28) << algoName
                      << " | " << std::right << std::setw(7) << threads
                      << " | " << std::fixed << std::setw(16) << std::setprecision(4) << elapsed.count()
                      << " |\n";
        }
    }

    std::cout << "--------------------------------------------------------------\n\n";
}

// Function to count total possible move sequences
void countTotalMoves(Engine &engine, StockDory::Board &chessBoard, int depth) {
    std::cout << "Counting total possible move sequences up to depth " << depth << "...\n";

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    // Count the moves
    uint64_t totalMoveSequences = engine.countMoves(chessBoard, depth);

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Display the result
    std::cout << "Total possible move sequences up to depth " << depth << ": " << totalMoveSequences << "\n";
    std::cout << "Time taken: " << std::fixed << std::setprecision(4) << elapsed.count() << " seconds.\n\n";
}

int main(int argc, char* argv[]) {
    // Check if the depth argument is provided
    if (argc != 2) {
        std::cerr << "Error: Incorrect number of arguments.\n";
        printUsage(argv[0]);
        return 1;
    }

    // Parse the depth from the first command-line argument
    int depth = std::atoi(argv[1]);

    // Validate the depth
    if (depth <= 0) {
        std::cerr << "Invalid depth: " << depth << ". Depth must be a positive integer.\n";
        printUsage(argv[0]);
        return 1;
    }

    // Initialize the engine
    Engine engine;

    // Display algorithm options and get user choice
    int algorithmChoice = 0;
    while (true) {
        displayAlgorithmOptions();
        std::cin >> algorithmChoice;

        // Check for input failure (e.g., non-integer input)
        if (std::cin.fail()) {
            std::cin.clear(); // Clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cerr << "Invalid input. Please enter 1, 2, 3, 4, or 5.\n";
            continue;
        }

        if (algorithmChoice >= 1 && algorithmChoice <= 5) {
            break; // Valid choice
        } else {
            std::cerr << "Invalid choice: " << algorithmChoice << ". Please enter 1, 2, 3, 4, or 5.\n";
        }
    }

    // Clear the newline character left in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Handle the user's choice
    if (algorithmChoice == 4) { // Run Performance Tests
        std::cout << "Running Performance Tests...\n";
        runPerformanceTests(depth);
        return 0; // Exit after testing
    }
    else if (algorithmChoice == 5) { // Count Total Possible Move Sequences
        // Initialize the chess board
        StockDory::Board chessBoard;

        // Prompt the user to input the initial FEN
        std::string initialFEN;
        while (true) {
            std::cout << "Enter the initial FEN string (or press Enter to use the standard starting position): ";
            std::getline(std::cin, initialFEN);

            if (initialFEN.empty()) {
                // Use the standard starting position
                initialFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
                std::cout << "Using standard starting position.\n";
            }

            try {
                chessBoard.SetFEN(initialFEN);
                break; // Successfully set FEN
            }
            catch (const std::exception& e) {
                std::cerr << "Failed to set FEN: " << e.what() << "\n";
                std::cout << "Please enter a valid FEN string.\n";
            }
        }

        // Count and display the total move sequences
        countTotalMoves(engine, chessBoard, depth);

        return 0; // Exit after counting
    }

    // If the user chose a parallel algorithm, prompt for the number of threads
    if (algorithmChoice >= 1 && algorithmChoice <= 3) {
        int threadCount;
        while (true) {
            std::cout << "Enter the number of threads to use for parallel algorithms: ";
            std::cin >> threadCount;
            if (std::cin.fail() || threadCount <= 0) {
                std::cin.clear(); // Clear the error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cerr << "Invalid thread count. Please enter a positive integer.\n";
                continue;
            } else {
                engine.setNumThreads(threadCount);
                break; // Valid thread count entered
            }
        }
        // Clear the newline character left in the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Map the choice to algorithm name
    std::string algorithmName;
    switch (algorithmChoice) {
        case 1:
            algorithmName = "Young Brothers Wait Concept (YBWC)";
            break;
        case 2:
            algorithmName = "Principal Variation Search (PVS)";
            break;
        case 3:
            algorithmName = "Parallel Alpha-Beta Nega";
            break;
        default:
            // This case should never occur due to the earlier validation
            algorithmName = "Unknown Algorithm";
            break;
    }

    std::cout << "Starting " << algorithmName << " with depth: " << depth << "\n\n";

    // Initialize the chess board
    StockDory::Board chessBoard;

    // Prompt the user to input the initial FEN
    std::string initialFEN;
    while (true) {
        std::cout << "Enter the initial FEN string (or press Enter to use the standard starting position): ";
        std::getline(std::cin, initialFEN);

        if (initialFEN.empty()) {
            // Use the standard starting position
            initialFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
            std::cout << "Using standard starting position.\n";
        }

        try {
            chessBoard.SetFEN(initialFEN);
            break; // Successfully set FEN
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to set FEN: " << e.what() << "\n";
            std::cout << "Please enter a valid FEN string.\n";
        }
    }

    // Main game loop
    while (true) {
        // Display the current board state
        std::cout << "Current FEN: " << chessBoard.Fen() << "\n";

        // Determine which color is to move
        Color currentPlayer = chessBoard.ColorToMove();

        std::cout << "Current Player: " 
                  << (currentPlayer == White ? "White" : "Black") << "\n";

        // Define a pair to hold the result (best move sequence and its score)
        std::pair<std::array<Move, maxDepth>, float> result;

        // Execute the appropriate search algorithm based on the user's choice and current player
        if (algorithmChoice == 1) { // YBWC
            if (currentPlayer == White) {
                std::cout << "Performing YBWC for White...\n";
                // Perform YBWC for White
                result = engine.YBWC<White, maxDepth>(
                    chessBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );

                // Extract the best move
                Move bestMove = result.first[0];
                std::cout << "White's Best Move (YBWC): "
                          << squareToString(bestMove.From()) << " to "
                          << squareToString(bestMove.To())
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    // Assuming that an invalid move has From() == To()
                    if (move.From() == move.To()) {
                        break; // Stop printing further moves
                    }
                    std::cout << squareToString(move.From()) << " to "
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board using the existing Move<0> method
                try {
                    chessBoard.Move<0>(bestMove.From(), bestMove.To());
                    std::cout << "Move executed successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error executing move: " << e.what() << "\n";
                    return 1;
                }
            }
            else if (currentPlayer == Black) {
                std::cout << "Performing YBWC for Black...\n";
                // Perform YBWC for Black
                result = engine.YBWC<Black, maxDepth>(
                    chessBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );

                // Extract the best move
                Move bestMove = result.first[0];
                std::cout << "Black's Best Move (YBWC): "
                          << squareToString(bestMove.From()) << " to "
                          << squareToString(bestMove.To())
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    if (move.From() == move.To()) {
                        break;
                    }
                    std::cout << squareToString(move.From()) << " to "
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board using the existing Move<0> method
                try {
                    chessBoard.Move<0>(bestMove.From(), bestMove.To());
                    std::cout << "Move executed successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error executing move: " << e.what() << "\n";
                    return 1;
                }
            }
        }
        else if (algorithmChoice == 2) { // PVS
            if (currentPlayer == White) {
                std::cout << "Performing PVS for White...\n";
                // Perform PVS for White
                result = engine.PVS<White, maxDepth>(
                    chessBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );

                // Extract the best move
                Move bestMove = result.first[0];
                std::cout << "White's Best Move (PVS): "
                          << squareToString(bestMove.From()) << " to "
                          << squareToString(bestMove.To())
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    if (move.From() == move.To()) {
                        break;
                    }
                    std::cout << squareToString(move.From()) << " to "
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board using the existing Move<0> method
                try {
                    chessBoard.Move<0>(bestMove.From(), bestMove.To());
                    std::cout << "Move executed successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error executing move: " << e.what() << "\n";
                    return 1;
                }
            }
            else if (currentPlayer == Black) {
                std::cout << "Performing PVS for Black...\n";
                // Perform PVS for Black
                result = engine.PVS<Black, maxDepth>(
                    chessBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );

                // Extract the best move
                Move bestMove = result.first[0];
                std::cout << "Black's Best Move (PVS): "
                          << squareToString(bestMove.From()) << " to "
                          << squareToString(bestMove.To())
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    if (move.From() == move.To()) {
                        break;
                    }
                    std::cout << squareToString(move.From()) << " to "
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board using the existing Move<0> method
                try {
                    chessBoard.Move<0>(bestMove.From(), bestMove.To());
                    std::cout << "Move executed successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error executing move: " << e.what() << "\n";
                    return 1;
                }
            }
        }
        else if (algorithmChoice == 3) { // Parallel Alpha-Beta Nega
            if (currentPlayer == White) {
                std::cout << "Performing Parallel Alpha-Beta Nega for White...\n";
                // Perform Parallel Alpha-Beta Nega for White
                result = engine.parallelAlphaBetaNega<White, maxDepth>(
                    chessBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );

                // Extract the best move
                Move bestMove = result.first[0];
                std::cout << "White's Best Move (Parallel Alpha-Beta Nega): "
                          << squareToString(bestMove.From()) << " to "
                          << squareToString(bestMove.To())
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    if (move.From() == move.To()) {
                        break;
                    }
                    std::cout << squareToString(move.From()) << " to "
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board using the existing Move<0> method
                try {
                    chessBoard.Move<0>(bestMove.From(), bestMove.To());
                    std::cout << "Move executed successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error executing move: " << e.what() << "\n";
                    return 1;
                }
            }
            else if (currentPlayer == Black) {
                std::cout << "Performing Parallel Alpha-Beta Nega for Black...\n";
                // Perform Parallel Alpha-Beta Nega for Black
                result = engine.parallelAlphaBetaNega<Black, maxDepth>(
                    chessBoard,
                    -std::numeric_limits<float>::infinity(),
                    std::numeric_limits<float>::infinity(),
                    depth
                );

                // Extract the best move
                Move bestMove = result.first[0];
                std::cout << "Black's Best Move (Parallel Alpha-Beta Nega): "
                          << squareToString(bestMove.From()) << " to "
                          << squareToString(bestMove.To())
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    if (move.From() == move.To()) {
                        break;
                    }
                    std::cout << squareToString(move.From()) << " to "
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board using the existing Move<0> method
                try {
                    chessBoard.Move<0>(bestMove.From(), bestMove.To());
                    std::cout << "Move executed successfully.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error executing move: " << e.what() << "\n";
                    return 1;
                }
            }
        }

        // Display the updated board state
        std::cout << "\nUpdated FEN: " << chessBoard.Fen() << "\n";

        // Prompt the user for a new FEN input
        while (true) {
            std::cout << "\nEnter a new FEN string to update the board (or type 'exit' to quit): ";
            std::string userFEN;
            std::getline(std::cin, userFEN);

            // Check if the user wants to exit
            if (userFEN == "exit") {
                std::cout << "Exiting the chess engine.\n";
                return 0;
            }

            // Attempt to set the new FEN
            try {
                chessBoard.SetFEN(userFEN);
                std::cout << "Board updated successfully.\n\n";
                break; // Exit the FEN input loop and continue with the main game loop
            }
            catch (const std::exception& e) {
                std::cerr << "Failed to set FEN: " << e.what() << "\n";
                std::cout << "Please try again.\n\n";
                // Continue to prompt the user for a valid FEN
            }
        }

        // Continue the main game loop
    }

    // If the user chose a parallel algorithm, the main loop has already been handled above.

    return 0;
}

// int main() {
//     StockDory::Board chessBoard;
//     Engine engine;
//     int depth = 1;
//     const StockDory::SimplifiedMoveList<White> moveList(chessBoard);
//
//     std::cout << "White's possible moves:\n";
//     for (uint8_t i = 0; i < moveList.Count(); i++) {
//         Move nextMove = moveList[i];
//         std::cout << "Move " << static_cast<int>(i + 1) << ": "
//                   << squareToString(nextMove.From()) << " to "
//                   << squareToString(nextMove.To()) << "\n";
//     }
//
//     if (chessBoard.ColorToMove() == White) {
//         std::pair<std::array<Move, maxDepth>, float> result3 = engine.PVS<White, maxDepth>(chessBoard, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), depth);
//
//         // Check if there is at least one move in the sequence
//         if (!result3.first.empty()) {
//             Move bestMove = result3.first.front();
//             std::cout << "White Result is: " << squareToString(bestMove.From()) << " to " << squareToString(bestMove.To())
//                       << " with score " << result3.second << "\n";
//
//             // Print the entire sequence of moves
//             std::cout << "Best line: ";
//             for (int i = 0; i < depth; i++) {
//                 Move move = result3.first[i];
//                 std::cout << squareToString(move.From()) << " to " << squareToString(move.To()) << ", ";
//             }
//             std::cout << "\n";
//         } else {
//             std::cout << "No moves available for White.\n";
//         }
//     }
//     else if (chessBoard.ColorToMove() == Black) {
//         std::pair<std::array<Move, maxDepth>, float> result3 = engine.YBWC<Black, maxDepth>(chessBoard, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), depth);
//
//         // Check if there is at least one move in the sequence
//         if (!result3.first.empty()) {
//             Move bestMove = result3.first.front();
//             std::cout << "Black Result is: " << squareToString(bestMove.From()) << " to " << squareToString(bestMove.To())
//                       << " with score " << result3.second << "\n";
//
//             // Print the entire sequence of moves
//             std::cout << "Best line: ";
//             for (const Move &move : result3.first) {
//                 std::cout << squareToString(move.From()) << " to " << squareToString(move.To()) << ", ";
//             }
//             std::cout << "\n";
//         } else {
//             std::cout << "No moves available for Black.\n";
//         }
//     }
//     return 0;
// }


    /*
    // The following sections are commented out but can be enabled for alternative algorithms
    // Example: YBWC and PVS algorithms with varying depths
    // Uncomment and modify as needed
    */

    /*
    if (chessBoard.ColorToMove() == White) {
        std::pair<std::array<Move, maxDepth>, float> result3 = engine.YBWC<White, maxDepth>(
            chessBoard, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), 7);

        // Check if there is at least one move in the sequence
        if (!result3.first.empty()) {
            Move bestMove = result3.first.front();
            std::cout << "White Result is: " << squareToString(bestMove.From()) << " to " << squareToString(bestMove.To())
                      << " with score " << result3.second << "\n";

            // Print the entire sequence of moves
            std::cout << "Best line: ";
            for (const Move &move : result3.first) {
                std::cout << squareToString(move.From()) << " to " << squareToString(move.To()) << ", ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No moves available for White.\n";
        }
    }
    else if (chessBoard.ColorToMove() == Black) {
        std::pair<std::array<Move, maxDepth>, float> result3 = engine.YBWC<Black, maxDepth>(
            chessBoard, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), 2);

        // Check if there is at least one move in the sequence
        if (!result3.first.empty()) {
            Move bestMove = result3.first.front();
            std::cout << "Black Result is: " << squareToString(bestMove.From()) << " to " << squareToString(bestMove.To())
                      << " with score " << result3.second << "\n";

            // Print the entire sequence of moves
            std::cout << "Best line: ";
            for (const Move &move : result3.first) {
                std::cout << squareToString(move.From()) << " to " << squareToString(move.To()) << ", ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No moves available for Black.\n";
        }
    }

    if (chessBoard.ColorToMove() == White) {
        std::pair<std::array<Move, maxDepth>, float> result3 = engine.PVS<White, maxDepth>(
            chessBoard, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), 7);

        // Check if there is at least one move in the sequence
        if (!result3.first.empty()) {
            Move bestMove = result3.first.front();
            std::cout << "White Result is: " << squareToString(bestMove.From()) << " to " << squareToString(bestMove.To())
                      << " with score " << result3.second << "\n";

            // Print the entire sequence of moves
            std::cout << "Best line: ";
            for (const Move &move : result3.first) {
                std::cout << squareToString(move.From()) << " to " << squareToString(move.To()) << ", ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No moves available for White.\n";
        }
    }
    else if (chessBoard.ColorToMove() == Black) {
        std::pair<std::array<Move, maxDepth>, float> result3 = engine.PVS<Black, maxDepth>(
            chessBoard, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), 2);

        // Check if there is at least one move in the sequence
        if (!result3.first.empty()) {
            Move bestMove = result3.first.front();
            std::cout << "Black Result is: " << squareToString(bestMove.From()) << " to " << squareToString(bestMove.To())
                      << " with score " << result3.second << "\n";

            // Print the entire sequence of moves
            std::cout << "Best line: ";
            for (const Move &move : result3.first) {
                std::cout << squareToString(move.From()) << " to " << squareToString(move.To()) << ", ";
            }
            std::cout << "\n";
        } else {
            std::cout << "No moves available for Black.\n";
        }
    }
    */

//     return 0;
// }
