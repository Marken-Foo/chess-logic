// NOTHING TO DO WITH POSITION_TESTS.CPP
#include "position.h"
#include "bitbord_lookup.h"

#include <cxxtest/TestSuite.h>

#include <memory> //for smart pointer

class TestSuitePosition: public CxxTest::TestSuite {
    // REWRITE WHOLE FILE TO MAKE TESTS DATA-DRIVEN
    // EP/PROMO TEST POSITION: 2b1k3/1Pp5/p7/1P1P4/5p1p/4P3/6Pp/4K1N1 w - - 0 1
    
    // CASTLING TEST POSITION:
    // r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1
    // atomic cap versions:
    // r3k2r/p7/4p3/3b4/3B4/4P3/P7/R3K2R w KQkq - 0 1
    // r3k2r/7p/4p3/4b3/4B3/4P3/7P/R3K2R w KQkq - 0 1
    
    
    // Test equality function is working correctly
    // > initialise 2 positions from FENs differing in 50/half counters (expect equal)
    // > test that equality is reflexive and symmetric
    
    // Test for captures
    // > For atomic, it will destroy lots of things - check pawns/nonpawns are correct.
    // > Check capturer/capturee pawns are destroyed
    
    // Test for promotions, promocaps (both colours)
    // > Test white and black promotions and promocaps. (16 combis)
    // > For atomic, promocaps will ofc destroy stuff.
    
    // Test for ep and doublemove rights being set correctly (both colours)
    // > Same position as promotions?
    
    // Test for castlings (all 4)
    // > Test that castling rights toggling is functioning correctly on make/unmake.
    //     - rights lost on K move, R move, capture, (atomic capture)
    // > Test that castlings yield correct positions.
    // > Test that unmaking castlings also yield correct positions.
    
    
    // EXTRA TESTS: COMBINE
    // > test that castling rights are lost upon promocap (or promocapexplosion) of rook, even to rook promotion!
    
    std::unique_ptr<Position> posKiwipete;
    std::unique_ptr<Position> refKiwipete;
    
    public:
    void setUp() {
        initialiseBbLookup();
        // sets up Kiwipete perft test position afresh
        posKiwipete = std::make_unique<Position>();
        posKiwipete->fromFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/"
                             "PPPBBPPP/R3K2R w KQkq - 0 1");
        
        refKiwipete = std::make_unique<Position>();
        refKiwipete->fromFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/"
                             "PPPBBPPP/R3K2R w KQkq - 0 1");
    }
    
    void tearDown() {
        posKiwipete.reset();
        return;
    }
    
    void testMakeLegalMove() {
        // 1.Ne5-c6 in Kiwipete
        Square fromSq = SQ_E5;
        Square toSq = SQ_C6;
        Piece pc = WN;
        Colour co = getPieceColour(pc);
        PieceType pcty = getPieceType(pc);
        Move mv = buildMove(fromSq, toSq);
        posKiwipete->makeMove(mv);
        TS_ASSERT(!(posKiwipete->getUnitsBb(co, pcty) & fromSq));
        TS_ASSERT(posKiwipete->getUnitsBb(co, pcty) & toSq);
        TS_ASSERT_EQUALS(posKiwipete->getMailbox()[fromSq], NO_PIECE);
        TS_ASSERT_EQUALS(posKiwipete->getMailbox()[toSq], pc);
    }
    
    void testMakeUnmake() {
        Square fromSq = SQ_E5;
        Square toSq = SQ_C6;
        Move mv = buildMove(fromSq, toSq);
        posKiwipete->makeMove(mv);
        posKiwipete->unmakeMove(mv);
        
        TS_ASSERT_EQUALS(*posKiwipete, *refKiwipete);
    }
    
};