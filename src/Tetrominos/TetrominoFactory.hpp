#include <memory>
#include "Tetromino.hpp"
#include "ITetromino.hpp"
#include "JTetromino.hpp"
#include "LTetromino.hpp"
#include "OTetromino.hpp"
#include "STetromino.hpp"
#include "TTetromino.hpp"
#include "ZTetromino.hpp"

enum TetrominoKind {
    ITetrominoKind,
    OTetrominoKind,
    TTetrominoKind,
    JTetrominoKind,
    LTetrominoKind,
    STetrominoKind,
    ZTetrominoKind
};


class TetrominoFactory
{
private:
    TetrominoFactory(/* args */);
    ~TetrominoFactory();
public:    
    static std::shared_ptr<Tetromino> Create(TetrominoKind tKind);
    
};

std::shared_ptr<Tetromino> TetrominoFactory::Create(TetrominoKind tKind) {
    switch (tKind)
    {
    case 0:
        return std::make_shared<ITetromino>();
        break;
    case 1:
        return std::make_shared<OTetromino>();
        break;
    case 2:
        return std::make_shared<TTetromino>();
        break;
    case 3:
        return std::make_shared<JTetromino>();
        break;
    case 4:
        return std::make_shared<LTetromino>();
        break;
    case 5:
        return std::make_shared<STetromino>();
        break;
    case 6:
        return std::make_shared<ZTetromino>();
        break;

    default:
        return std::make_shared<Tetromino>();
        break;
    }

    return std::make_shared<Tetromino>();
}