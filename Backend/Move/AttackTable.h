//
// Copyright (c) 2023 StockDory authors. See the list of authors for more details.
// Licensed under LGPL-3.0.
//

#ifndef STOCKDORY_ATTACKTABLE_H
#define STOCKDORY_ATTACKTABLE_H

#include <array>

#include "BlackMagicFactory.h"

#include "../Type/BitBoard.h"
#include "../Type/Piece.h"

#include "../Util.h"

namespace StockDory
{

    class AttackTable
    {

        public:

            constexpr static std::array<std::array<BitBoard, 64>, 2> Pawn {{
                {   // BEGIN WHITE
                    0x0000000000000200, 0x0000000000000500, 0x0000000000000a00, 0x0000000000001400,
                    0x0000000000002800, 0x0000000000005000, 0x000000000000a000, 0x0000000000004000,
                    0x0000000000020000, 0x0000000000050000, 0x00000000000a0000, 0x0000000000140000,
                    0x0000000000280000, 0x0000000000500000, 0x0000000000a00000, 0x0000000000400000,
                    0x0000000002000000, 0x0000000005000000, 0x000000000a000000, 0x0000000014000000,
                    0x0000000028000000, 0x0000000050000000, 0x00000000a0000000, 0x0000000040000000,
                    0x0000000200000000, 0x0000000500000000, 0x0000000a00000000, 0x0000001400000000,
                    0x0000002800000000, 0x0000005000000000, 0x000000a000000000, 0x0000004000000000,
                    0x0000020000000000, 0x0000050000000000, 0x00000a0000000000, 0x0000140000000000,
                    0x0000280000000000, 0x0000500000000000, 0x0000a00000000000, 0x0000400000000000,
                    0x0002000000000000, 0x0005000000000000, 0x000a000000000000, 0x0014000000000000,
                    0x0028000000000000, 0x0050000000000000, 0x00a0000000000000, 0x0040000000000000,
                    0x0200000000000000, 0x0500000000000000, 0x0a00000000000000, 0x1400000000000000,
                    0x2800000000000000, 0x5000000000000000, 0xa000000000000000, 0x4000000000000000,
                    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
                    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000
                },  // END WHITE
                {   // BEGIN BLACK
                    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
                    0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000,
                    0x0000000000000002, 0x0000000000000005, 0x000000000000000a, 0x0000000000000014,
                    0x0000000000000028, 0x0000000000000050, 0x00000000000000a0, 0x0000000000000040,
                    0x0000000000000200, 0x0000000000000500, 0x0000000000000a00, 0x0000000000001400,
                    0x0000000000002800, 0x0000000000005000, 0x000000000000a000, 0x0000000000004000,
                    0x0000000000020000, 0x0000000000050000, 0x00000000000a0000, 0x0000000000140000,
                    0x0000000000280000, 0x0000000000500000, 0x0000000000a00000, 0x0000000000400000,
                    0x0000000002000000, 0x0000000005000000, 0x000000000a000000, 0x0000000014000000,
                    0x0000000028000000, 0x0000000050000000, 0x00000000a0000000, 0x0000000040000000,
                    0x0000000200000000, 0x0000000500000000, 0x0000000a00000000, 0x0000001400000000,
                    0x0000002800000000, 0x0000005000000000, 0x000000a000000000, 0x0000004000000000,
                    0x0000020000000000, 0x0000050000000000, 0x00000a0000000000, 0x0000140000000000,
                    0x0000280000000000, 0x0000500000000000, 0x0000a00000000000, 0x0000400000000000,
                    0x0002000000000000, 0x0005000000000000, 0x000a000000000000, 0x0014000000000000,
                    0x0028000000000000, 0x0050000000000000, 0x00a0000000000000, 0x0040000000000000
                }   // END BLACK
            }};

            constexpr static std::array<BitBoard, 64> Knight {
                0x0000000000020400, 0x0000000000050800, 0x00000000000A1100, 0x0000000000142200,
                0x0000000000284400, 0x0000000000508800, 0x0000000000A01000, 0x0000000000402000,
                0x0000000002040004, 0x0000000005080008, 0x000000000A110011, 0x0000000014220022,
                0x0000000028440044, 0x0000000050880088, 0x00000000A0100010, 0x0000000040200020,
                0x0000000204000402, 0x0000000508000805, 0x0000000A1100110A, 0x0000001422002214,
                0x0000002844004428, 0x0000005088008850, 0x000000A0100010A0, 0x0000004020002040,
                0x0000020400040200, 0x0000050800080500, 0x00000A1100110A00, 0x0000142200221400,
                0x0000284400442800, 0x0000508800885000, 0x0000A0100010A000, 0x0000402000204000,
                0x0002040004020000, 0x0005080008050000, 0x000A1100110A0000, 0x0014220022140000,
                0x0028440044280000, 0x0050880088500000, 0x00A0100010A00000, 0x0040200020400000,
                0x0204000402000000, 0x0508000805000000, 0x0A1100110A000000, 0x1422002214000000,
                0x2844004428000000, 0x5088008850000000, 0xA0100010A0000000, 0x4020002040000000,
                0x0400040200000000, 0x0800080500000000, 0x1100110A00000000, 0x2200221400000000,
                0x4400442800000000, 0x8800885000000000, 0x100010A000000000, 0x2000204000000000,
                0x0004020000000000, 0x0008050000000000, 0x00110A0000000000, 0x0022140000000000,
                0x0044280000000000, 0x0088500000000000, 0x0010A00000000000, 0x0020400000000000
            };

            constexpr static std::array<BitBoard, 64> King {
                0x0000000000000302, 0x0000000000000705, 0x0000000000000E0A, 0x0000000000001C14,
                0x0000000000003828, 0x0000000000007050, 0x000000000000E0A0, 0x000000000000C040,
                0x0000000000030203, 0x0000000000070507, 0x00000000000E0A0E, 0x00000000001C141C,
                0x0000000000382838, 0x0000000000705070, 0x0000000000E0A0E0, 0x0000000000C040C0,
                0x0000000003020300, 0x0000000007050700, 0x000000000E0A0E00, 0x000000001C141C00,
                0x0000000038283800, 0x0000000070507000, 0x00000000E0A0E000, 0x00000000C040C000,
                0x0000000302030000, 0x0000000705070000, 0x0000000E0A0E0000, 0x0000001C141C0000,
                0x0000003828380000, 0x0000007050700000, 0x000000E0A0E00000, 0x000000C040C00000,
                0x0000030203000000, 0x0000070507000000, 0x00000E0A0E000000, 0x00001C141C000000,
                0x0000382838000000, 0x0000705070000000, 0x0000E0A0E0000000, 0x0000C040C0000000,
                0x0003020300000000, 0x0007050700000000, 0x000E0A0E00000000, 0x001C141C00000000,
                0x0038283800000000, 0x0070507000000000, 0x00E0A0E000000000, 0x00C040C000000000,
                0x0302030000000000, 0x0705070000000000, 0x0E0A0E0000000000, 0x1C141C0000000000,
                0x3828380000000000, 0x7050700000000000, 0xE0A0E00000000000, 0xC040C00000000000,
                0x0203000000000000, 0x0507000000000000, 0x0A0E000000000000, 0x141C000000000000,
                0x2838000000000000, 0x5070000000000000, 0xA0E0000000000000, 0x40C0000000000000
            };

            static std::array<BitBoard, 87988> Sliding;

    };

} // StockDory

std::array<BitBoard, 87988> StockDory::AttackTable::Sliding = []() {
    std::array<BitBoard, 87988> temp = std::array<BitBoard, 87988>();

    const std::array<std::array<std::pair<int8_t, int8_t>, 4>, 2> deltaStride = {{
        {{{ 1,  1 },{ 1, -1 },{ -1, -1 },{ -1,  1 }}}, {{{ 1,  0 },{ 0, -1 },{ -1,  0 },{ 0,  1 }}}
    }};

    using MagicPair = std::pair<BitBoard, BitBoard>;

    for (uint8_t i = 0; i < 2; i++) {
        const auto p = static_cast<Piece>(i + 2);
        const std::array<std::pair<MagicPair, int32_t>, 64>& magic = StockDory::BlackMagicFactory::Magic[i];
        const std::array<std::pair<int8_t   ,  int8_t>,  4>& delta = deltaStride[i];

        for (uint8_t h = 0; h < 8; h++) for (uint8_t v = 0; v < 8; v++) {
            auto sq = static_cast<Square>(v * 8 + h);

            // Black Magic:
            BitBoard mask = ~(magic[sq].first.second);
            BitBoard occ  = BBDefault;

            // Enumeration:
            while (true) {
                BitBoard moves = BBDefault;

                for (std::pair<int8_t, int8_t> stride : delta) {
                    auto hI = static_cast<int8_t>(h);
                    auto vI = static_cast<int8_t>(v);

                    while (!Get(occ, static_cast<Square>(vI * 8 + hI))) {
                        auto dHI = static_cast<int8_t>(hI + stride.first );
                        auto dVI = static_cast<int8_t>(vI + stride.second);

                        if (dHI > 7 || dHI < 0) break;
                        if (dVI > 7 || dVI < 0) break;

                        hI = static_cast<int8_t>(hI + stride.first );
                        vI = static_cast<int8_t>(vI + stride.second);

                        moves |= FromSquare(static_cast<Square>(vI * 8 + hI));
                    }
                }

                // List insertion:
                uint32_t idx = StockDory::BlackMagicFactory::MagicIndex(p, sq, occ);
                temp[idx] = moves;

                // Occupation Recalculation:
                occ = (occ - mask) & mask;

                // Skipping count:
                if (Count(occ) == 0) break;
            }
        }
    }

    return temp;
}();

#endif //STOCKDORY_ATTACKTABLE_H