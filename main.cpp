#include <Graphics.hpp>
#include <vector>
#include <iostream>

constexpr short BOARD_HEIGHT = 8;
constexpr short BOARD_WIDTH = 8;
constexpr float TILE_SIZE = 60.f;

enum class CHESS
{
    EMPTY,
    QUEEN,
    KING,
    ROOK,
    BISHOP,
    PAWN,
    KNIGHT
};

class ChessPiece
{
public:
    sf::Vector2i pos;
    bool team;
    CHESS piece_type;

    ChessPiece() : pos(0, 0), team(false), piece_type(CHESS::EMPTY) {}

    ChessPiece(sf::Vector2i pos, bool team, CHESS piece_type)
        : pos(pos), team(team), piece_type(piece_type) {}
};


void createStartingPositioning(std::vector<std::vector<ChessPiece>>& vec)
{
    // BLACK BACK ROW
    vec[0][0] = ChessPiece(sf::Vector2i(0, 0), false, CHESS::ROOK);
    vec[0][1] = ChessPiece(sf::Vector2i(0, 1), false, CHESS::KNIGHT);
    vec[0][2] = ChessPiece(sf::Vector2i(0, 2), false, CHESS::BISHOP);
    vec[0][3] = ChessPiece(sf::Vector2i(0, 3), false, CHESS::QUEEN);
    vec[0][4] = ChessPiece(sf::Vector2i(0, 4), false, CHESS::KING);
    vec[0][5] = ChessPiece(sf::Vector2i(0, 5), false, CHESS::BISHOP);
    vec[0][6] = ChessPiece(sf::Vector2i(0, 6), false, CHESS::KNIGHT);
    vec[0][7] = ChessPiece(sf::Vector2i(0, 7), false, CHESS::ROOK);
    // BLACK FRONT ROW
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        vec[1][i] = ChessPiece(sf::Vector2i(1, i), false, CHESS::PAWN);
    }

    // WHITE BACK ROW
    vec[7][0] = ChessPiece(sf::Vector2i(7, 0), true, CHESS::ROOK);
    vec[7][1] = ChessPiece(sf::Vector2i(7, 1), true, CHESS::KNIGHT);
    vec[7][2] = ChessPiece(sf::Vector2i(7, 2), true, CHESS::BISHOP);
    vec[7][3] = ChessPiece(sf::Vector2i(7, 3), true, CHESS::QUEEN);
    vec[7][4] = ChessPiece(sf::Vector2i(7, 4), true, CHESS::KING);
    vec[7][5] = ChessPiece(sf::Vector2i(7, 5), true, CHESS::BISHOP);
    vec[7][6] = ChessPiece(sf::Vector2i(7, 6), true, CHESS::KNIGHT);
    vec[7][7] = ChessPiece(sf::Vector2i(7, 7), true, CHESS::ROOK);
    // WHITE FRONT ROW
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        vec[6][i] = ChessPiece(sf::Vector2i(6, i), true, CHESS::PAWN);
    }
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(BOARD_WIDTH * TILE_SIZE, BOARD_HEIGHT * TILE_SIZE), "chess engine", sf::Style::Default);
    window.setFramerateLimit(60);

    // load the textures
    sf::Texture pawn_b;
    if(!pawn_b.loadFromFile("./res/pawn_b.png"))
        std::cout << "pawn_b not loaded \n";
    sf::Texture pawn_w;
    if(!pawn_w.loadFromFile("./res/pawn_w.png"))
        std::cout << "pawn_w not loaded \n";

    sf::Texture king_b;
    if(!king_b.loadFromFile("./res/king_b.png"))
        std::cout << "king_b not loaded \n";
    sf::Texture king_w;
    if(!king_w.loadFromFile("./res/king_w.png"))
        std::cout << "king_w not loaded \n";

    sf::Texture rook_b;
    if(!rook_b.loadFromFile("./res/rook_b.png"))
        std::cout << "rook_b not loaded \n";
    sf::Texture rook_w;
    if(!rook_w.loadFromFile("./res/rook_w.png"))
        std::cout << "rook_w not loaded \n";

    sf::Texture bishop_b;
    if(!bishop_b.loadFromFile("./res/bishop_b.png"))
        std::cout << "bishop_b not loaded \n";
    sf::Texture bishop_w;
    if(!bishop_w.loadFromFile("./res/bishop_w.png"))
        std::cout << "bishop_w not loaded \n";

    sf::Texture knight_b;
    if(!knight_b.loadFromFile("./res/knight_b.png"))
        std::cout << "knight_b not loaded \n";
    sf::Texture knight_w;
    if(!knight_w.loadFromFile("./res/knight_w.png"))
        std::cout << "knight_w not loaded \n";

    sf::Texture queen_b;
    if(!queen_b.loadFromFile("./res/queen_b.png"))
        std::cout << "queen_b not loaded \n";
    sf::Texture queen_w;
    if(!queen_w.loadFromFile("./res/queen_w.png"))
        std::cout << "queen_w not loaded \n";

    // Create the board tile enumaration
    std::vector<std::vector<int>> board(BOARD_WIDTH, std::vector<int>(BOARD_HEIGHT));
    int count = 0;
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        for(int k = 0; k < BOARD_HEIGHT; k++)
        {
            board[i][k] = count;
            count++;
        }
    }
    // Create the tilemap
    std::vector<sf::RectangleShape> tiles;
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        for(int k = 0; k < BOARD_HEIGHT; k++)
        {
            sf::RectangleShape tile;
            tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setPosition(i * TILE_SIZE, k * TILE_SIZE);
            if ((i + k) % 2 == 0)
            {
                tile.setFillColor(sf::Color(20, 122, 27));
            }
            else
            {
                tile.setFillColor(sf::Color(234, 240, 119));
            }
            tiles.emplace_back(tile);
        }
    }
    // Create the board pieces info
    std::vector<std::vector<ChessPiece>> board_data(BOARD_WIDTH, std::vector<ChessPiece>(BOARD_HEIGHT));
    createStartingPositioning(board_data);

    while (window.isOpen())
    {
        sf::Event event{};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        // draw chessboard
        for(int i = 0; i < tiles.size(); i++)
        {
            window.draw(tiles[i]);
        }

        // draw the pieces
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            for (int k = 0; k < BOARD_HEIGHT; k++)
            {
                const ChessPiece& piece_info = board_data[k][i];
                if (piece_info.piece_type != CHESS::EMPTY)
                {
                    sf::Sprite piece;
                    switch (piece_info.piece_type)
                    {
                        case CHESS::PAWN:
                            piece.setTexture(piece_info.team ? pawn_w : pawn_b);
                        break;
                        case CHESS::ROOK:
                            piece.setTexture(piece_info.team ? rook_w : rook_b);
                        break;
                        case CHESS::KNIGHT:
                            piece.setTexture(piece_info.team ? knight_w : knight_b);
                        break;
                        case CHESS::BISHOP:
                            piece.setTexture(piece_info.team ? bishop_w : bishop_b);
                        break;
                        case CHESS::QUEEN:
                            piece.setTexture(piece_info.team ? queen_w : queen_b);
                        break;
                        case CHESS::KING:
                            piece.setTexture(piece_info.team ? king_w : king_b);
                        break;
                        default:
                            continue; // skip empty tiles
                    }
                    piece.setPosition(i * TILE_SIZE, k * TILE_SIZE);
                    window.draw(piece);
                }
            }
        }

        window.display();
    }
}
