// main.cpp
#include <iostream>
#include <limits>
#include <string>
#include <cstdlib> // For std::atoi

#include "Backend/Board.h"         // Include Board.h for chess board representation
#include "Backend/Type/Square.h"   // Include Square.h to use the Square enum
#include "SimplifiedMoveList.h"    // Include your SimplifiedMoveList class
#include "Backend/Type/Color.h"
#include "Engine.h"                // Include your Engine class

// Function to convert a Square enum to its string representation (e.g., E2 -> "e2")
std::string squareToString(Square square) {
    return std::string(1, File(square)) + std::string(1, Rank(square));
}

int main(int argc, char* argv[]) {
    // Check if the depth argument is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <depth>\n";
        std::cerr << "Please provide the search depth as a command-line argument.\n";
        return 1;
    }

    // Parse the depth from the first command-line argument
    int depth = std::atoi(argv[1]);

    // Validate the depth
    if (depth <= 0) {
        std::cerr << "Invalid depth: " << depth << ". Depth must be a positive integer.\n";
        return 1;
    }

    std::cout << "Starting Minimax with depth: " << depth << "\n\n";

    // Initialize the chess board with the default FEN
    StockDory::Board chessBoard;

    // Initialize the engine
    Engine engine;

    // Main game loop
    while (true) {
        // Display the current board state
        std::cout << "Current FEN: " << chessBoard.Fen() << "\n";

        // Determine which color is to move
        Color currentPlayer = chessBoard.ColorToMove();

        // Define a pair to hold the result (best move sequence and its score)
        std::pair<std::vector<Move>, float> result;

        // Execute the appropriate search algorithm based on the current player
        if (currentPlayer == White) {
            std::cout << "White to move.\n";

            // Perform alpha-beta pruning for White
            result = engine.alphaBetaNega<White>(
                chessBoard,
                -std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity(),
                depth
            );

            // Check if there is at least one move in the sequence
            if (!result.first.empty()) {
                Move bestMove = result.first.front();
                std::cout << "White's Best Move: " 
                          << squareToString(bestMove.From()) << " to " 
                          << squareToString(bestMove.To()) 
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    std::cout << squareToString(move.From()) << " to " 
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board
                chessBoard.Move<0>(bestMove.From(), bestMove.To());

            } else {
                std::cout << "No moves available for White.\n";
            }
        }
        else if (currentPlayer == Black) {
            std::cout << "Black to move.\n";

            // Perform alpha-beta pruning for Black
            result = engine.alphaBetaNega<Black>(
                chessBoard,
                -std::numeric_limits<float>::infinity(),
                std::numeric_limits<float>::infinity(),
                depth
            );

            // Check if there is at least one move in the sequence
            if (!result.first.empty()) {
                Move bestMove = result.first.front();
                std::cout << "Black's Best Move: " 
                          << squareToString(bestMove.From()) << " to " 
                          << squareToString(bestMove.To()) 
                          << " with score " << result.second << "\n";

                // Print the entire sequence of moves (best line)
                std::cout << "Best Line: ";
                for (const Move &move : result.first) {
                    std::cout << squareToString(move.From()) << " to " 
                              << squareToString(move.To()) << ", ";
                }
                std::cout << "\n";

                // Execute the move on the board
                chessBoard.Move<0>(bestMove.From(), bestMove.To());

            } else {
                std::cout << "No moves available for Black.\n";
            }
        }

        // Display the updated board state
        std::cout << "\nUpdated FEN: " << chessBoard.Fen() << "\n";

        // Prompt the user for a new FEN input
        std::cout << "\nEnter a new FEN string to update the board (or type 'exit' to quit): ";
        std::string userFEN;
        std::getline(std::cin, userFEN);

        // Check if the user wants to exit
        if (userFEN == "exit") {
            std::cout << "Exiting the chess engine.\n";
            break;
        }

        // Attempt to set the new FEN
        try {
            chessBoard.SetFEN(userFEN);
            std::cout << "Board updated successfully.\n\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to set FEN: " << e.what() << "\n";
            std::cout << "Please try again.\n\n";
            // Continue to the next iteration without executing the engine
            continue;
        }

        // The loop will rerun the engine with the same depth using the updated board
    }

    return 0;
}
