#pragma once
#include <glm/glm.hpp>
#include <unordered_map>

namespace std 
{
    template<>
        struct hash<glm::vec2>
        {   
            public:
                std::size_t operator()(glm::vec2 const& coord) const 
                {   
                    /*  
                    size_t x = coord.x;

                                      x = 00000000 00000000 00000000 00000000 01234567 89abcdef ghijklmn opqrstuv
                                          01234567 89abcdef ghijklmn opqrstuv 00000000 00000000 00000000 00000000 << 32
                                          01234567 89abcdef ghijklmn opqrstuv 01234567 89abcdef ghijklmn opqrstuv | x
                                          11111111 11111111 00000000 00000000 00000000 00000000 11111111 11111111 &
                                      x = 01234567 89abcdef 00000000 00000000 00000000 00000000 ghijklmn opqrstuv
                                          00000000 00000000 00000000 00000000 ghijklmn opqrstuv 00000000 00000000 << 16
                                          01234567 89abcdef 00000000 00000000 ghijklmn opqrstuv ghijklmn opqrstuv | x
                                          00000000 11111111 00000000 00000000 11111111 00000000 00000000 11111111 &
                                      x = 00000000 89abcdef 00000000 00000000 ghijklmn 00000000 00000000 opqrstuv 
                                          89abcdef 00000000 00000000 ghijklmn 00000000 00000000 opqrstuv 00000000 << 8
                                          89abcdef 89abcdef 00000000 ghijklmn ghijklmn 00000000 opqrstuv opqrstuv | x
                                          11110000 00001111 00000000 11110000 00001111 00000000 11110000 00001111 &
                                      x = 89ab0000 0000cdef 00000000 ghij0000 0000klmn 00000000 opqr0000 0000stuv
                                          00000000 cdef0000 0000ghij 00000000 klmn0000 0000opqr 00000000 stuv0000 << 4
                                          89ab0000 cdefcdef 0000ghij ghij0000 klmnklmn 0000opqr opqr0000 stuvstuv | x
                                          00110000 11000011 00001100 00110000 11000011 00001100 00110000 11000011 &
                                      x = 00ab0000 cd0000ef 0000gh00 00ij0000 kl0000mn 0000op00 00qr0000 st0000uv
                                          ab0000cd 0000ef00 00gh0000 ij0000kl 0000mn00 00op0000 qr0000st 0000uv00 << 2
                                          abab00cd cd00efef 00ghgh00 ijij00kl kl00mnmn 00opop00 qrqr00st st00uvuv | x
                                          10010010 01001001 00100100 10010010 01001001 00100100 10010010 01001001 &
                                      x = a00b00c0 0d00e00f 00g00h00 i00j00k0 0l00m00n 00o00p00 q00r00s0 0t00u00v
                                      */
                    size_t x = (size_t)(coord.x * 1000);
                    x = (x | (x << 16)) & 0x00FF0000FF0000FF;
                    x = (x | (x << 8))  & 0xF00F00F00F00F00F;
                    x = (x | (x << 4))  & 0x30C30C30C30C30C3;
                    x = (x | (x << 2))  & 0x9249249249249249;

                    size_t y = (size_t)(coord.y * 1000);
                    y = (y | (y << 16)) & 0x00FF0000FF0000FF;
                    y = (y | (y << 8))  & 0xF00F00F00F00F00F;
                    y = (y | (y << 4))  & 0x30C30C30C30C30C3;
                    y = (y | (y << 2))  & 0x9249249249249249;

                    return x | (y << 1); 
                }   
        };  

    template<>
        struct hash<glm::ivec2>
        {   
            public:
                std::size_t operator()(glm::ivec2 const& coord) const 
                {   
                    /*  
                    size_t x = coord.x;

                                      x = 00000000 00000000 00000000 00000000 01234567 89abcdef ghijklmn opqrstuv
                                          01234567 89abcdef ghijklmn opqrstuv 00000000 00000000 00000000 00000000 << 32
                                          01234567 89abcdef ghijklmn opqrstuv 01234567 89abcdef ghijklmn opqrstuv | x
                                          11111111 11111111 00000000 00000000 00000000 00000000 11111111 11111111 &
                                      x = 01234567 89abcdef 00000000 00000000 00000000 00000000 ghijklmn opqrstuv
                                          00000000 00000000 00000000 00000000 ghijklmn opqrstuv 00000000 00000000 << 16
                                          01234567 89abcdef 00000000 00000000 ghijklmn opqrstuv ghijklmn opqrstuv | x
                                          00000000 11111111 00000000 00000000 11111111 00000000 00000000 11111111 &
                                      x = 00000000 89abcdef 00000000 00000000 ghijklmn 00000000 00000000 opqrstuv 
                                          89abcdef 00000000 00000000 ghijklmn 00000000 00000000 opqrstuv 00000000 << 8
                                          89abcdef 89abcdef 00000000 ghijklmn ghijklmn 00000000 opqrstuv opqrstuv | x
                                          11110000 00001111 00000000 11110000 00001111 00000000 11110000 00001111 &
                                      x = 89ab0000 0000cdef 00000000 ghij0000 0000klmn 00000000 opqr0000 0000stuv
                                          00000000 cdef0000 0000ghij 00000000 klmn0000 0000opqr 00000000 stuv0000 << 4
                                          89ab0000 cdefcdef 0000ghij ghij0000 klmnklmn 0000opqr opqr0000 stuvstuv | x
                                          00110000 11000011 00001100 00110000 11000011 00001100 00110000 11000011 &
                                      x = 00ab0000 cd0000ef 0000gh00 00ij0000 kl0000mn 0000op00 00qr0000 st0000uv
                                          ab0000cd 0000ef00 00gh0000 ij0000kl 0000mn00 00op0000 qr0000st 0000uv00 << 2
                                          abab00cd cd00efef 00ghgh00 ijij00kl kl00mnmn 00opop00 qrqr00st st00uvuv | x
                                          10010010 01001001 00100100 10010010 01001001 00100100 10010010 01001001 &
                                      x = a00b00c0 0d00e00f 00g00h00 i00j00k0 0l00m00n 00o00p00 q00r00s0 0t00u00v
                                      */
                    size_t x = coord.x;
                    x = (x | (x << 16)) & 0x00FF0000FF0000FF;
                    x = (x | (x << 8))  & 0xF00F00F00F00F00F;
                    x = (x | (x << 4))  & 0x30C30C30C30C30C3;
                    x = (x | (x << 2))  & 0x9249249249249249;

                    size_t y = coord.y;
                    y = (y | (y << 16)) & 0x00FF0000FF0000FF;
                    y = (y | (y << 8))  & 0xF00F00F00F00F00F;
                    y = (y | (y << 4))  & 0x30C30C30C30C30C3;
                    y = (y | (y << 2))  & 0x9249249249249249;

                    return x | (y << 1); 
                }   
        };  

    template<>
        struct hash<glm::uvec2>
        {   
            public:
                std::size_t operator()(glm::uvec2 const& coord) const 
                {   
                    /*  
                    size_t x = coord.x;

                                      x = 00000000 00000000 00000000 00000000 01234567 89abcdef ghijklmn opqrstuv
                                          01234567 89abcdef ghijklmn opqrstuv 00000000 00000000 00000000 00000000 << 32
                                          01234567 89abcdef ghijklmn opqrstuv 01234567 89abcdef ghijklmn opqrstuv | x
                                          11111111 11111111 00000000 00000000 00000000 00000000 11111111 11111111 &
                                      x = 01234567 89abcdef 00000000 00000000 00000000 00000000 ghijklmn opqrstuv
                                          00000000 00000000 00000000 00000000 ghijklmn opqrstuv 00000000 00000000 << 16
                                          01234567 89abcdef 00000000 00000000 ghijklmn opqrstuv ghijklmn opqrstuv | x
                                          00000000 11111111 00000000 00000000 11111111 00000000 00000000 11111111 &
                                      x = 00000000 89abcdef 00000000 00000000 ghijklmn 00000000 00000000 opqrstuv 
                                          89abcdef 00000000 00000000 ghijklmn 00000000 00000000 opqrstuv 00000000 << 8
                                          89abcdef 89abcdef 00000000 ghijklmn ghijklmn 00000000 opqrstuv opqrstuv | x
                                          11110000 00001111 00000000 11110000 00001111 00000000 11110000 00001111 &
                                      x = 89ab0000 0000cdef 00000000 ghij0000 0000klmn 00000000 opqr0000 0000stuv
                                          00000000 cdef0000 0000ghij 00000000 klmn0000 0000opqr 00000000 stuv0000 << 4
                                          89ab0000 cdefcdef 0000ghij ghij0000 klmnklmn 0000opqr opqr0000 stuvstuv | x
                                          00110000 11000011 00001100 00110000 11000011 00001100 00110000 11000011 &
                                      x = 00ab0000 cd0000ef 0000gh00 00ij0000 kl0000mn 0000op00 00qr0000 st0000uv
                                          ab0000cd 0000ef00 00gh0000 ij0000kl 0000mn00 00op0000 qr0000st 0000uv00 << 2
                                          abab00cd cd00efef 00ghgh00 ijij00kl kl00mnmn 00opop00 qrqr00st st00uvuv | x
                                          10010010 01001001 00100100 10010010 01001001 00100100 10010010 01001001 &
                                      x = a00b00c0 0d00e00f 00g00h00 i00j00k0 0l00m00n 00o00p00 q00r00s0 0t00u00v
                                      */
                    size_t x = coord.x;
                    x = (x | (x << 16)) & 0x00FF0000FF0000FF;
                    x = (x | (x << 8))  & 0xF00F00F00F00F00F;
                    x = (x | (x << 4))  & 0x30C30C30C30C30C3;
                    x = (x | (x << 2))  & 0x9249249249249249;

                    size_t y = coord.y;
                    y = (y | (y << 16)) & 0x00FF0000FF0000FF;
                    y = (y | (y << 8))  & 0xF00F00F00F00F00F;
                    y = (y | (y << 4))  & 0x30C30C30C30C30C3;
                    y = (y | (y << 2))  & 0x9249249249249249;

                    return x | (y << 1); 
                }   
        };  
}
