
#include "sound.h"
#include "timer.h"
#include "globals.h"
#include "dac.h"

// All audio at 8000Hz, 4-bit PCM encoded
unsigned char g_soundMove[SND_MOVE_LENGTH] = {0x87, 0x54, 0x58, 0xab, 0x96, 0x44, 0x7a, 0xa9, 0x52, 0x14, 0x8b, 0xa8, 0x54, 0x58, 0xaa, 0x63, 0x13, 0x7a, 0xb9, 0x64, 0x47, 0xaa, 0x85, 0x22, 0x59, 0xbb, 0x85, 0x46, 0x9b, 0xa7, 0x31, 0x36, 0xab, 0xa6, 0x44, 0x7a, 0xa8, 0x52, 0x25, 0x9b, 0xb8, 0x54, 0x58, 0xba, 0x73, 0x13, 0x6a, 0xb9, 0x64, 0x47, 0xaa, 0x85, 0x21, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa6, 0x31, 0x26, 0xab, 0x96, 0x44, 0x79, 0xa8, 0x41, 0x14, 0x8b, 0xb8, 0x54, 0x58, 0xa9, 0x63, 0x12, 0x6a, 0xba, 0x64, 0x47, 0xaa, 0x95, 0x21, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa7, 0x31, 0x26, 0xab, 0x96, 0x44, 0x79, 0xa8, 0x51, 0x14, 0x8b, 0xb8, 0x54, 0x58, 0xaa, 0x73, 0x12, 0x6a, 0xb9, 0x64, 0x46, 0x9a, 0x84, 0x11, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa7, 0x31, 0x26, 0x9b, 0x96, 0x44, 0x69, 0xa8, 0x41, 0x14, 0x8b, 0xb8, 0x54, 0x58, 0xaa, 0x73, 0x12, 0x6a, 0xba, 0x64, 0x46, 0x9a, 0x85, 0x11, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa7, 0x31, 0x26, 0x9b, 0xa6, 0x44, 0x69, 0xa9, 0x52, 0x14, 0x8a, 0xa8, 0x53, 0x58, 0xa9, 0x73, 0x12, 0x6a, 0xba, 0x64, 0x46, 0x9b, 0x95, 0x21, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa7, 0x31, 0x26, 0x9b, 0xa7, 0x44, 0x69, 0xa9, 0x52, 0x13, 0x8c, 0xdb, 0x84, 0x34, 0x7a, 0xba, 0x73, 0x10, 0x36, 0xac, 0xb8, 0x53, 0x35, 0x9b, 0xb8, 0x41, 0x2, 0x59, 0xcc, 0x96, 0x33, 0x58, 0xab, 0x95, 0x20, 0x14, 0x8b, 0xca, 0x74, 0x34, 0x7a, 0xba, 0x63, 0x0, 0x37, 0xbc, 0xb8, 0x53, 0x36, 0x9b, 0xa7, 0x41, 0x2, 0x6a, 0xcb, 0x95, 0x33, 0x58, 0xbb, 0x85, 0x10, 0x15, 0x9c, 0xca, 0x64, 0x34, 0x7a, 0xb9, 0x62, 0x1, 0x48, 0xbc, 0xa7, 0x43, 0x47, 0xab, 0xa7, 0x30, 0x3, 0x6a, 0xcb, 0x85, 0x33, 0x69, 0xba, 0x84, 0x10, 0x25, 0x9c, 0xc9, 0x63, 0x35, 0x8a, 0xb9, 0x52, 0x1, 0x48, 0xbc, 0xa7, 0x43, 0x47, 0xab, 0x96, 0x20, 0x3, 0x7b, 0xcb, 0x85, 0x34, 0x69, 0xba, 0x84, 0x10, 0x26, 0xac, 0xb9, 0x53, 0x35, 0x8b, 0xa8, 0x41, 0x1, 0x59, 0xcc, 0xa6, 0x43, 0x58, 0xab, 0x96, 0x20, 0x14, 0x8b, 0xca, 0x74, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x37, 0xac, 0xb8, 0x53, 0x36, 0x9b, 0xa8, 0x41, 0x2, 0x69, 0xcc, 0x96, 0x33, 0x58, 0xab, 0x95, 0x20, 0x14, 0x8b, 0xca, 0x74, 0x34, 0x7a, 0xba, 0x63, 0x1, 0x37, 0xbc, 0xb8, 0x53, 0x46, 0x9b, 0xa7, 0x31, 0x2, 0x6a, 0xcb, 0x95, 0x33, 0x58, 0xbb, 0x85, 0x20, 0x25, 0x9c, 0xca, 0x64, 0x35, 0x8a, 0xb9, 0x62, 0x11, 0x48, 0xbc, 0xb7, 0x43, 0x47, 0xab, 0x96, 0x20, 0x26, 0xac, 0xa7, 0x44, 0x59, 0xba, 0x73, 0x11, 0x59, 0xbb, 0x85, 0x34, 0x7a, 0xb9, 0x51, 0x13, 0x7b, 0xca, 0x64, 0x46, 0x9b, 0xa6, 0x20, 0x26, 0xac, 0xb8, 0x54, 0x58, 0xaa, 0x74, 0x11, 0x48, 0xbb, 0x95, 0x44, 0x7a, 0xb9, 0x52, 0x13, 0x7a, 0xca, 0x74, 0x36, 0x9b, 0xa7, 0x31, 0x25, 0x9c, 0xb8, 0x53, 0x58, 0xab, 0x84, 0x11, 0x48, 0xbc, 0x96, 0x44, 0x7a, 0xb9, 0x62, 0x12, 0x6a, 0xcb, 0x74, 0x46, 0x9b, 0xa7, 0x31, 0x14, 0x9b, 0xb9, 0x53, 0x47, 0xab, 0x95, 0x21, 0x37, 0xbc, 0xa6, 0x44, 0x69, 0xba, 0x62, 0x2, 0x6a, 0xcb, 0x85, 0x35, 0x8a, 0xb8, 0x41, 0x14, 0x9c, 0xc9, 0x64, 0x47, 0xab, 0x95, 0x21, 0x37, 0xac, 0xa7, 0x44, 0x69, 0xba, 0x73, 0x12, 0x59, 0xcb, 0x85, 0x35, 0x8a, 0xb8, 0x41, 0x14, 0x8b, 0xca, 0x64, 0x46, 0x9b, 0x96, 0x21, 0x26, 0xac, 0xb8, 0x54, 0x69, 0xba, 0x73, 0x11, 0x49, 0xbb, 0x95, 0x34, 0x7a, 0xb9, 0x52, 0x13, 0x7b, 0xca, 0x64, 0x46, 0x9b, 0xa6, 0x31, 0x26, 0xac, 0xb8, 0x53, 0x58, 0xaa, 0x84, 0x11, 0x48, 0xcc, 0x96, 0x44, 0x7a, 0xb9, 0x52, 0x13, 0x7a, 0xca, 0x74, 0x46, 0x9b, 0xa7, 0x31, 0x25, 0x9c, 0xb8, 0x53, 0x48, 0xbb, 0x84, 0x11, 0x48, 0xbb, 0x96, 0x44, 0x69, 0xaa, 0x74, 0x10, 0x26, 0xad, 0xeb, 0x73, 0x24, 0x7a, 0xba, 0x85, 0x31, 0x12, 0x59, 0xce, 0xc8, 0x42, 0x36, 0x9b, 0xb9, 0x64, 0x21, 0x13, 0x7b, 0xed, 0xa5, 0x22, 0x48, 0xbb, 0xa7, 0x53, 0x11, 0x25, 0x9d, 0xeb, 0x73, 0x23, 0x7a, 0xba, 0x86, 0x42, 0x11, 0x48, 0xce, 0xd9, 0x42, 0x25, 0x9b, 0xb9, 0x74, 0x21, 0x12, 0x6a, 0xde, 0xb6, 0x32, 0x47, 0xab, 0xa8, 0x63, 0x21, 0x24, 0x8c, 0xec, 0x84, 0x23, 0x69, 0xbb, 0x97, 0x42, 0x11, 0x37, 0xbe, 0xd9, 0x52, 0x25, 0x8b, 0xba, 0x75, 0x31, 0x12, 0x6a, 0xde, 0xb7, 0x31, 0x37, 0xab, 0xa8, 0x63, 0x21, 0x24, 0x8c, 0xec, 0x84, 0x22, 0x59, 0xbb, 0x97, 0x42, 0x11, 0x36, 0xad, 0xda, 0x62, 0x24, 0x8a, 0xba, 0x85, 0x31, 0x12, 0x59, 0xde, 0xc8, 0x31, 0x36, 0x9b, 0xb9, 0x64, 0x21, 0x13, 0x7b, 0xed, 0x95, 0x22, 0x58, 0xbb, 0xa7, 0x53, 0x11, 0x25, 0x9d, 0xeb, 0x73, 0x13, 0x7a, 0xba, 0x86, 0x32, 0x12, 0x48, 0xce, 0xc8, 0x41, 0x26, 0x9b, 0xb9, 0x64, 0x21, 0x13, 0x7b, 0xed, 0xa5, 0x22, 0x48, 0xab, 0xa7, 0x53, 0x11, 0x25, 0x9d, 0xec, 0x73, 0x13, 0x6a, 0xbb, 0x86, 0x42, 0x11, 0x37, 0xbe, 0xd9, 0x52, 0x25, 0x8b, 0xb9, 0x75, 0x21, 0x12, 0x6a, 0xdd, 0xb6, 0x32, 0x37, 0xab, 0xb8, 0x63, 0x11, 0x25, 0x9c, 0xdb, 0x74, 0x35, 0x8b, 0xca, 0x62, 0x1, 0x48, 0xbc, 0xb7, 0x43, 0x47, 0xab, 0xa7, 0x30, 0x3, 0x7b, 0xcb, 0x85, 0x34, 0x69, 0xbb, 0x84, 0x10, 0x25, 0xac, 0xc9, 0x63, 0x35, 0x8b, 0xb9, 0x51, 0x1, 0x49, 0xcc, 0xa7, 0x43, 0x47, 0xab, 0xa6, 0x20, 0x3, 0x8b, 0xdb, 0x84, 0x33, 0x69, 0xba, 0x73, 0x0, 0x26, 0xac, 0xc9, 0x53, 0x35, 0x8b, 0xa8, 0x41, 0x2, 0x59, 0xcc, 0xa6, 0x43, 0x58, 0xab, 0x95, 0x20, 0x14, 0x8c, 0xca, 0x74, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x37, 0xbc, 0xb8, 0x53, 0x36, 0x9b, 0xb8, 0x41, 0x2, 0x6a, 0xcc, 0x95, 0x33, 0x58, 0xbb, 0x95, 0x10, 0x15, 0x9c, 0xca, 0x64, 0x34, 0x7a, 0xba, 0x62, 0x0, 0x38, 0xbc, 0xb7, 0x43, 0x47, 0x9b, 0xa7, 0x30, 0x3, 0x7a, 0xcb, 0x85, 0x33, 0x69, 0xbb, 0x84, 0x10, 0x15, 0x9c, 0xca, 0x63, 0x35, 0x8b, 0xb9, 0x52, 0x1, 0x48, 0xcc, 0xa7, 0x43, 0x47, 0xab, 0xa6, 0x20, 0x3, 0x7b, 0xcb, 0x85, 0x34, 0x69, 0xba, 0x73, 0x0, 0x26, 0xac, 0xc9, 0x63, 0x35, 0x8b, 0xb9, 0x51, 0x1, 0x59, 0xcc, 0xa7, 0x43, 0x47, 0xab, 0xa6, 0x20, 0x3, 0x8b, 0xcb, 0x84, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x27, 0xac, 0xb8, 0x53, 0x36, 0x9b, 0xb8, 0x41, 0x1, 0x5a, 0xcc, 0x95, 0x33, 0x59, 0xbb, 0x96, 0x42, 0x21, 0x23, 0x6b, 0xef, 0xc8, 0x30, 0x15, 0x9b, 0xb9, 0x75, 0x43, 0x21, 0x24, 0x7b, 0xee, 0xb6, 0x21, 0x26, 0x9b, 0xb9, 0x65, 0x43, 0x21, 0x25, 0x8c, 0xed, 0xa5, 0x11, 0x37, 0xab, 0xa8, 0x64, 0x32, 0x21, 0x25, 0x9d, 0xed, 0x94, 0x11, 0x47, 0xbc, 0xa8, 0x64, 0x32, 0x12, 0x36, 0xad, 0xec, 0x83, 0x11, 0x58, 0xbb, 0xa7, 0x54, 0x32, 0x12, 0x37, 0xbe, 0xeb, 0x62, 0x12, 0x59, 0xbb, 0x97, 0x54, 0x32, 0x12, 0x48, 0xce, 0xea, 0x62, 0x13, 0x6a, 0xbb, 0x97, 0x54, 0x32, 0x12, 0x59, 0xde, 0xd9, 0x51, 0x13, 0x7a, 0xcb, 0x86, 0x53, 0x21, 0x12, 0x5a, 0xdf, 0xd9, 0x41, 0x14, 0x8b, 0xca, 0x85, 0x43, 0x22, 0x23, 0x6a, 0xee, 0xc7, 0x31, 0x25, 0x9b, 0xba, 0x75, 0x43, 0x21, 0x24, 0x7b, 0xee, 0xb6, 0x21, 0x26, 0x9b, 0xb9, 0x75, 0x33, 0x21, 0x25, 0x8c, 0xee, 0xa5, 0x21, 0x37, 0xab, 0xb8, 0x64, 0x33, 0x21, 0x25, 0x9d, 0xed, 0x94, 0x11, 0x48, 0xbc, 0xa8, 0x64, 0x32, 0x21, 0x36, 0xad, 0xec, 0x83, 0x11, 0x48, 0xbb, 0xa7, 0x54, 0x32, 0x22, 0x37, 0xbe, 0xeb, 0x73, 0x12, 0x59, 0xbb, 0xa7, 0x54, 0x32, 0x12, 0x48, 0xce, 0xea, 0x62, 0x12, 0x6a, 0xbb, 0x97, 0x54, 0x32, 0x12, 0x59, 0xcf, 0xd9, 0x51, 0x13, 0x7a, 0xba, 0x86, 0x43, 0x11, 0x26, 0xad, 0xda, 0x62, 0x13, 0x7a, 0xca, 0x85, 0x31, 0x1, 0x48, 0xce, 0xd8, 0x41, 0x25, 0x9b, 0xb9, 0x74, 0x21, 0x12, 0x6b, 0xee, 0xa6, 0x21, 0x48, 0xab, 0xa8, 0x53, 0x11, 0x25, 0x9d, 0xec, 0x83, 0x12, 0x6a, 0xbb, 0x96, 0x42, 0x11, 0x37, 0xbe, 0xd9, 0x52, 0x24, 0x8b, 0xba, 0x75, 0x21, 0x12, 0x5a, 0xde, 0xb7, 0x31, 0x37, 0xab, 0xa8, 0x63, 0x11, 0x14, 0x8c, 0xec, 0x84, 0x12, 0x69, 0xbb, 0x96, 0x42, 0x11, 0x37, 0xbe, 0xea, 0x52, 0x24, 0x8b, 0xba, 0x75, 0x31, 0x12, 0x59, 0xde, 0xc7, 0x31, 0x36, 0xab, 0xb9, 0x64, 0x21, 0x13, 0x7c, 0xed, 0x95, 0x22, 0x59, 0xbb, 0x97, 0x42, 0x11, 0x26, 0xad, 0xeb, 0x62, 0x13, 0x7a, 0xba, 0x85, 0x31, 0x11, 0x48, 0xce, 0xd8, 0x41, 0x26, 0x9b, 0xb9, 0x74, 0x21, 0x13, 0x6b, 0xed, 0xa5, 0x22, 0x48, 0xbb, 0xa7, 0x52, 0x11, 0x25, 0xad, 0xeb, 0x73, 0x13, 0x7a, 0xbb, 0x86, 0x32, 0x11, 0x48, 0xce, 0xd9, 0x41, 0x25, 0x9b, 0xb9, 0x74, 0x21, 0x12, 0x6a, 0xee, 0xb6, 0x21, 0x47, 0xab, 0xa8, 0x53, 0x11, 0x14, 0x8c, 0xec, 0x83, 0x12, 0x69, 0xbb, 0x96, 0x42, 0x11, 0x37, 0xbe, 0xea, 0x52, 0x24, 0x8b, 0xba, 0x75, 0x31, 0x12, 0x59, 0xde, 0xc7, 0x31, 0x36, 0xac, 0xb8, 0x63, 0x21, 0x23, 0x6a, 0xdf, 0xeb, 0x61, 0x2, 0x59, 0xbb, 0xa7, 0x65, 0x43, 0x21, 0x25, 0x9d, 0xfe, 0xb6, 0x20, 0x25, 0x9b, 0xba, 0x76, 0x54, 0x32, 0x12, 0x59, 0xcf, 0xeb, 0x62, 0x12, 0x59, 0xbb, 0xa8, 0x65, 0x43, 0x21, 0x25, 0x8c, 0xfe, 0xb6, 0x21, 0x25, 0x8b, 0xba, 0x86, 0x54, 0x32, 0x12, 0x48, 0xcf, 0xeb, 0x72, 0x12, 0x58, 0xbb, 0xa8, 0x65, 0x43, 0x21, 0x24, 0x8c, 0xfe, 0xb7, 0x31, 0x25, 0x8b, 0xba, 0x86, 0x54, 0x32, 0x12, 0x48, 0xce, 0xeb, 0x73, 0x11, 0x48, 0xbb, 0xa8, 0x65, 0x43, 0x22, 0x24, 0x8c, 0xef, 0xc7, 0x31, 0x14, 0x8b, 0xba, 0x86, 0x54, 0x32, 0x12, 0x47, 0xbe, 0xfc, 0x73, 0x11, 0x48, 0xab, 0xa8, 0x65, 0x43, 0x21, 0x24, 0x7b, 0xee, 0xc8, 0x31, 0x14, 0x8a, 0xba, 0x86, 0x54, 0x32, 0x12, 0x47, 0xbe, 0xfc, 0x83, 0x11, 0x48, 0xab, 0xa8, 0x65, 0x43, 0x21, 0x23, 0x7b, 0xef, 0xc8, 0x41, 0x14, 0x7a, 0xba, 0x86, 0x54, 0x32, 0x22, 0x37, 0xbe, 0xfc, 0x84, 0x11, 0x47, 0xab, 0xa8, 0x65, 0x43, 0x21, 0x24, 0x7b, 0xde, 0xd9, 0x51, 0x3, 0x7b, 0xdb, 0x73, 0x1, 0x59, 0xbc, 0xa7, 0x54, 0x43, 0x21, 0x25, 0x9c, 0xfe, 0xb6, 0x21, 0x25, 0x8b, 0xba, 0x75, 0x44, 0x55, 0x55, 0x55, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x67, 0x77, 0x77, 0x67, 0x77, 0x76, 0x67, 0x89, 0x98, 0x64, 0x46, 0x9b, 0xa8, 0x54, 0x68, 0xaa, 0x73, 0x13, 0x6a, 0xb9, 0x64, 0x47, 0xaa, 0x84, 0x12, 0x59, 0xbb, 0x85, 0x46, 0x9a, 0xa6, 0x31, 0x37, 0xab, 0x96, 0x45, 0x7a, 0xb8, 0x52, 0x25, 0x9b, 0xb8, 0x54, 0x69, 0xa9, 0x63, 0x13, 0x7b, 0xc9, 0x64, 0x57, 0xab, 0x85, 0x22, 0x59, 0xbb, 0x85, 0x46, 0x9a, 0xa6, 0x31, 0x37, 0xab, 0x96, 0x44, 0x7a, 0xa8, 0x41, 0x14, 0x8b, 0xa8, 0x54, 0x58, 0xa9, 0x63, 0x13, 0x6a, 0xb9, 0x64, 0x47, 0xaa, 0x84, 0x11, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa6, 0x31, 0x26, 0xab, 0x96, 0x44, 0x79, 0xa8, 0x41, 0x14, 0x8b, 0xa8, 0x54, 0x58, 0xa9, 0x63, 0x12, 0x6a, 0xb9, 0x64, 0x47, 0x9a, 0x84, 0x11, 0x48, 0xba, 0x85, 0x45, 0x8a, 0x96, 0x21, 0x26, 0xab, 0x96, 0x44, 0x7a, 0xa8, 0x41, 0x14, 0x8b, 0xa8, 0x53, 0x58, 0xa9, 0x62, 0x12, 0x6a, 0xb9, 0x64, 0x47, 0xaa, 0x84, 0x11, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa6, 0x31, 0x26, 0xab, 0x96, 0x44, 0x79, 0xa8, 0x41, 0x14, 0x8b, 0xb8, 0x54, 0x58, 0xaa, 0x73, 0x12, 0x69, 0xb9, 0x64, 0x46, 0x9a, 0x84, 0x11, 0x48, 0xbb, 0x85, 0x45, 0x8a, 0xa7, 0x31, 0x26, 0xab, 0xa6, 0x44, 0x69, 0xa8, 0x51, 0x14, 0x8b, 0xb8, 0x53, 0x58, 0xaa, 0x73, 0x12, 0x6a, 0xdc, 0x96, 0x33, 0x69, 0xba, 0x85, 0x10, 0x15, 0x9c, 0xca, 0x63, 0x34, 0x7a, 0xb9, 0x62, 0x1, 0x37, 0xbc, 0xb7, 0x43, 0x46, 0x9b, 0xa7, 0x31, 0x3, 0x7a, 0xcb, 0x85, 0x33, 0x69, 0xbb, 0x84, 0x10, 0x25, 0x9c, 0xc9, 0x63, 0x35, 0x8a, 0xb9, 0x52, 0x1, 0x48, 0xbc, 0xa7, 0x43, 0x47, 0xab, 0xa7, 0x30, 0x3, 0x7b, 0xcb, 0x85, 0x33, 0x69, 0xba, 0x74, 0x10, 0x26, 0xac, 0xb9, 0x53, 0x35, 0x8b, 0xb9, 0x51, 0x1, 0x59, 0xcc, 0xa6, 0x43, 0x47, 0xab, 0x96, 0x20, 0x4, 0x8b, 0xca, 0x74, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x26, 0xac, 0xb8, 0x53, 0x36, 0x9b, 0xa8, 0x41, 0x2, 0x59, 0xcc, 0x96, 0x33, 0x58, 0xab, 0x95, 0x20, 0x14, 0x8b, 0xca, 0x74, 0x34, 0x7a, 0xb9, 0x62, 0x0, 0x37, 0xbc, 0xb8, 0x53, 0x46, 0x9b, 0xa8, 0x41, 0x2, 0x6a, 0xcc, 0x95, 0x33, 0x58, 0xbb, 0x85, 0x10, 0x15, 0x9c, 0xca, 0x64, 0x35, 0x7a, 0xb9, 0x62, 0x1, 0x48, 0xbc, 0xb8, 0x43, 0x47, 0xab, 0xa7, 0x30, 0x3, 0x7a, 0xcb, 0x85, 0x33, 0x69, 0xba, 0x84, 0x10, 0x26, 0xac, 0xc9, 0x63, 0x35, 0x8b, 0xb9, 0x52, 0x1, 0x48, 0xbc, 0xa7, 0x43, 0x47, 0xab, 0xa7, 0x30, 0x13, 0x7b, 0xcb, 0x84, 0x34, 0x69, 0xba, 0x74, 0x10, 0x26, 0xac, 0xc9, 0x53, 0x35, 0x9b, 0xa7, 0x31, 0x14, 0x8b, 0xb8, 0x53, 0x47, 0xab, 0x95, 0x21, 0x37, 0xbc, 0xa6, 0x44, 0x69, 0xba, 0x63, 0x12, 0x59, 0xcb, 0x85, 0x35, 0x8a, 0xa8, 0x41, 0x14, 0x8b, 0xc9, 0x64, 0x47, 0xab, 0x95, 0x20, 0x26, 0xac, 0xa7, 0x44, 0x69, 0xba, 0x73, 0x11, 0x59, 0xcb, 0x85, 0x34, 0x8a, 0xb8, 0x51, 0x13, 0x8b, 0xca, 0x64, 0x46, 0x9b, 0xa6, 0x21, 0x26, 0xac, 0xb8, 0x44, 0x58, 0xba, 0x73, 0x11, 0x49, 0xbb, 0x95, 0x44, 0x7a, 0xb9, 0x51, 0x3, 0x7a, 0xca, 0x74, 0x46, 0x9b, 0xa7, 0x31, 0x25, 0xac, 0xb8, 0x53, 0x58, 0xbb, 0x84, 0x11, 0x48, 0xbc, 0x96, 0x44, 0x79, 0xb9, 0x62, 0x13, 0x7a, 0xcb, 0x75, 0x46, 0x9b, 0xa7, 0x31, 0x15, 0x9b, 0xb8, 0x54, 0x58, 0xab, 0x95, 0x11, 0x38, 0xbc, 0xa6, 0x44, 0x69, 0xb9, 0x62, 0x2, 0x6a, 0xcb, 0x85, 0x45, 0x8b, 0xa8, 0x41, 0x14, 0x9c, 0xc9, 0x64, 0x57, 0xab, 0x95, 0x21, 0x37, 0xac, 0xa7, 0x44, 0x69, 0xba, 0x73, 0x12, 0x6a, 0xcb, 0x85, 0x35, 0x8b, 0xb8, 0x41, 0x14, 0x8b, 0xc9, 0x64, 0x47, 0xab, 0x96, 0x21, 0x37, 0xac, 0xb7, 0x54, 0x69, 0xba, 0x73, 0x11, 0x59, 0xbb, 0x85, 0x35, 0x8a, 0xb9, 0x51, 0x13, 0x8b, 0xca, 0x63, 0x46, 0x9b, 0xa6, 0x20, 0x26, 0xab, 0xa7, 0x54, 0x58, 0xaa, 0x85, 0x20, 0x14, 0x9c, 0xec, 0x84, 0x23, 0x69, 0xbb, 0x97, 0x42, 0x11, 0x37, 0xbe, 0xda, 0x52, 0x25, 0x8b, 0xba, 0x75, 0x31, 0x12, 0x59, 0xde, 0xb7, 0x32, 0x37, 0xab, 0xb8, 0x64, 0x21, 0x14, 0x8c, 0xed, 0x95, 0x22, 0x59, 0xbb, 0x97, 0x53, 0x11, 0x36, 0xad, 0xeb, 0x63, 0x24, 0x7a, 0xba, 0x85, 0x32, 0x12, 0x48, 0xce, 0xc8, 0x42, 0x36, 0x9b, 0xb9, 0x74, 0x21, 0x13, 0x7b, 0xed, 0xa5, 0x22, 0x48, 0xbb, 0xa8, 0x53, 0x11, 0x25, 0x9d, 0xeb, 0x73, 0x23, 0x7a, 0xbb, 0x86, 0x42, 0x12, 0x48, 0xce, 0xd9, 0x41, 0x25, 0x9b, 0xb9, 0x74, 0x21, 0x13, 0x6a, 0xdd, 0xa6, 0x22, 0x47, 0xab, 0xa8, 0x53, 0x21, 0x25, 0x9c, 0xec, 0x84, 0x23, 0x69, 0xbb, 0x96, 0x42, 0x11, 0x37, 0xbe, 0xda, 0x52, 0x25, 0x8b, 0xba, 0x75, 0x31, 0x12, 0x59, 0xde, 0xb7, 0x31, 0x37, 0xab, 0xa8, 0x64, 0x21, 0x14, 0x8c, 0xed, 0x94, 0x22, 0x59, 0xbb, 0x97, 0x42, 0x11, 0x37, 0xbe, 0xda, 0x62, 0x24, 0x8b, 0xba, 0x85, 0x31, 0x12, 0x59, 0xde, 0xc7, 0x31, 0x36, 0xab, 0xa8, 0x64, 0x21, 0x13, 0x7b, 0xed, 0x95, 0x22, 0x58, 0xbb, 0x97, 0x52, 0x11, 0x26, 0xad, 0xeb, 0x63, 0x13, 0x7a, 0xba, 0x86, 0x32, 0x11, 0x48, 0xce, 0xc8, 0x42, 0x25, 0x8b, 0xb9, 0x74, 0x20, 0x14, 0x7b, 0xdc, 0x95, 0x34, 0x7a, 0xcb, 0x73, 0x0, 0x26, 0xac, 0xc9, 0x53, 0x35, 0x9b, 0xb8, 0x41, 0x1, 0x59, 0xcc, 0xa6, 0x43, 0x58, 0xbb, 0x96, 0x20, 0x4, 0x8b, 0xcb, 0x74, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x37, 0xbc, 0xb8, 0x53, 0x36, 0x9b, 0xb8, 0x41, 0x2, 0x6a, 0xcc, 0x96, 0x33, 0x58, 0xbb, 0x95, 0x10, 0x15, 0x9c, 0xca, 0x74, 0x34, 0x7a, 0xb9, 0x62, 0x1, 0x48, 0xbc, 0xb8, 0x43, 0x46, 0x9b, 0xa7, 0x30, 0x2, 0x6a, 0xcb, 0x85, 0x33, 0x59, 0xbb, 0x84, 0x10, 0x15, 0x9c, 0xca, 0x63, 0x35, 0x8a, 0xb9, 0x52, 0x1, 0x48, 0xbc, 0xa7, 0x43, 0x47, 0xab, 0xa7, 0x30, 0x3, 0x7b, 0xcb, 0x85, 0x33, 0x69, 0xbb, 0x84, 0x10, 0x26, 0xac, 0xc9, 0x63, 0x35, 0x8b, 0xb8, 0x41, 0x1, 0x59, 0xcc, 0xa7, 0x43, 0x47, 0xab, 0x96, 0x20, 0x3, 0x8b, 0xdb, 0x84, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x27, 0xac, 0xb8, 0x53, 0x36, 0x9b, 0xb8, 0x41, 0x1, 0x59, 0xcc, 0xa6, 0x33, 0x58, 0xab, 0x95, 0x10, 0x14, 0x8c, 0xca, 0x74, 0x34, 0x7a, 0xba, 0x73, 0x0, 0x37, 0xbc, 0xb8, 0x53, 0x36, 0x9b, 0xb8, 0x40, 0x2, 0x6a, 0xcc, 0x96, 0x33, 0x58, 0xbb, 0x95, 0x10, 0x15, 0x9c, 0xca, 0x63, 0x34, 0x7a, 0xb9, 0x62, 0x0, 0x38, 0xbd, 0xb7, 0x42, 0x47, 0xab, 0xa7, 0x53, 0x21, 0x12, 0x59, 0xdf, 0xea, 0x51, 0x13, 0x7a, 0xba, 0x86, 0x43, 0x21, 0x12, 0x6a, 0xdf, 0xd8, 0x41, 0x14, 0x8b, 0xba, 0x75, 0x43, 0x22, 0x23, 0x7b, 0xee, 0xc7, 0x31, 0x25, 0x9b, 0xb9, 0x75, 0x43, 0x21, 0x24, 0x7b, 0xee, 0xb6, 0x21, 0x26, 0x9b, 0xb9, 0x75, 0x43, 0x21, 0x24, 0x8c, 0xed, 0xa5, 0x11, 0x37, 0xac, 0xb8, 0x64, 0x32, 0x21, 0x25, 0x9d, 0xed, 0x84, 0x11, 0x48, 0xbc, 0xa8, 0x64, 0x32, 0x21, 0x36, 0xad, 0xec, 0x73, 0x11, 0x58, 0xbb, 0xa7, 0x54, 0x32, 0x12, 0x37, 0xbe, 0xeb, 0x72, 0x12, 0x59, 0xbb, 0x97, 0x54, 0x32, 0x12, 0x48, 0xce, 0xeb, 0x62, 0x13, 0x6a, 0xcb, 0x96, 0x43, 0x22, 0x12, 0x59, 0xce, 0xd9, 0x51, 0x13, 0x7a, 0xcb, 0x86, 0x43, 0x22, 0x13, 0x6a, 0xde, 0xd8, 0x41, 0x14, 0x8b, 0xca, 0x85, 0x43, 0x22, 0x23, 0x7b, 0xee, 0xc7, 0x31, 0x25, 0x9b, 0xba, 0x75, 0x43, 0x22, 0x24, 0x7b, 0xee, 0xb6, 0x21, 0x26, 0xac, 0xb9, 0x75, 0x33, 0x21, 0x24, 0x8c, 0xee, 0xa5, 0x11, 0x37, 0xab, 0xb8, 0x64, 0x33, 0x21, 0x25, 0x9d, 0xed, 0x94, 0x11, 0x48, 0xbc, 0xa8, 0x64, 0x32, 0x11, 0x36, 0xad, 0xec, 0x83, 0x11, 0x48, 0xbb, 0xa7, 0x54, 0x32, 0x12, 0x37, 0xbe, 0xeb, 0x72, 0x12, 0x69, 0xbb, 0x97, 0x53, 0x21, 0x14, 0x8c, 0xec, 0x83, 0x12, 0x59, 0xbb, 0x97, 0x42, 0x11, 0x26, 0xbe, 0xeb, 0x62, 0x14, 0x7b, 0xba, 0x85, 0x31, 0x1, 0x49, 0xde, 0xc8, 0x31, 0x26, 0x9b, 0xb9, 0x64, 0x21, 0x13, 0x7b, 0xed, 0xa5, 0x22, 0x48, 0xbb, 0xa7, 0x53, 0x11, 0x25, 0x9d, 0xeb, 0x73, 0x13, 0x7a, 0xbb, 0x86, 0x32, 0x1, 0x48, 0xce, 0xd9, 0x41, 0x25, 0x9b, 0xb9, 0x74, 0x21, 0x13, 0x6b, 0xed, 0xa5, 0x21, 0x48, 0xbb, 0xa7, 0x53, 0x11, 0x25, 0x9d, 0xec, 0x73, 0x13, 0x6a, 0xbb, 0x96, 0x42, 0x11, 0x37, 0xbe, 0xd9, 0x52, 0x25, 0x8b, 0xba, 0x75, 0x31, 0x12, 0x6a, 0xde, 0xb7, 0x31, 0x37, 0xab, 0xa8, 0x63, 0x21, 0x14, 0x8c, 0xed, 0x84, 0x12, 0x59, 0xbb, 0x97, 0x42, 0x11, 0x36, 0xbe, 0xea, 0x62, 0x14, 0x8b, 0xba, 0x85, 0x31, 0x12, 0x59, 0xde, 0xc7, 0x31, 0x36, 0xab, 0xb8, 0x63, 0x21, 0x14, 0x8c, 0xed, 0x94, 0x12, 0x59, 0xbb, 0x97, 0x42, 0x11, 0x26, 0xad, 0xeb, 0x62, 0x14, 0x7a, 0xba, 0x85, 0x31, 0x11, 0x49, 0xde, 0xc8, 0x31, 0x26, 0x9b, 0xb9, 0x64, 0x21, 0x13, 0x7b, 0xed, 0xa5, 0x22, 0x48, 0xbb, 0xa7, 0x53, 0x11, 0x25, 0x9d, 0xec, 0x73, 0x13, 0x6a, 0xbb, 0x86, 0x32, 0x11, 0x37, 0xbe, 0xd9, 0x52, 0x24, 0x8b, 0xca, 0x74, 0x21, 0x12, 0x58, 0xce, 0xfd, 0x83, 0x1, 0x48, 0xbc, 0xa8, 0x65, 0x43, 0x21, 0x23, 0x7b, 0xef, 0xc8, 0x41, 0x14, 0x7a, 0xba, 0x86, 0x54, 0x32, 0x22, 0x37, 0xbe, 0xfd, 0x84, 0x11, 0x37, 0xab, 0xa9, 0x75, 0x43, 0x22, 0x23, 0x7b, 0xef, 0xd8, 0x41, 0x13, 0x7a, 0xba, 0x97, 0x54, 0x32, 0x12, 0x37, 0xbe, 0xfd, 0x94, 0x11, 0x37, 0xab, 0xb9, 0x75, 0x43, 0x22, 0x13, 0x6a, 0xef, 0xd9, 0x41, 0x13, 0x7a, 0xbb, 0x97, 0x54, 0x32, 0x21, 0x36, 0xad, 0xfd, 0x94, 0x11, 0x37, 0xab, 0xb9, 0x75, 0x43, 0x22, 0x23, 0x6a, 0xdf, 0xd9, 0x51, 0x13, 0x6a, 0xbb, 0x97, 0x54, 0x33, 0x22, 0x36, 0xad, 0xfd, 0x95, 0x11, 0x36, 0xab, 0xb9, 0x75, 0x43, 0x32, 0x13, 0x6a, 0xdf, 0xda, 0x52, 0x13, 0x69, 0xbb, 0x97, 0x54, 0x33, 0x21, 0x25, 0x9d, 0xfe, 0xa5, 0x21, 0x36, 0x9b, 0xb9, 0x75, 0x43, 0x32, 0x12, 0x59, 0xdf, 0xea, 0x62, 0x12, 0x69, 0xbb, 0x97, 0x54, 0x33, 0x21, 0x25, 0x9d, 0xfe, 0xa6, 0x21, 0x26, 0x9b, 0xb9, 0x76, 0x43, 0x21, 0x12, 0x59, 0xce, 0xeb, 0x62, 0x1, 0x59, 0xcc, 0x95, 0x10, 0x37, 0xbc, 0xb8, 0x65, 0x43, 0x21, 0x13, 0x7b, 0xef, 0xc8, 0x41, 0x13, 0x7a, 0xbb, 0x86, 0x54, 0x45, 0x55, 0x55, 0x67, };
unsigned char g_soundBullet[SND_BULLET_LENGTH] = {0x12, 0x21, 0x11, 0x11, 0x11, 0x12, 0x11, 0x11, 0x11, 0x21, 0x12, 0x21, 0x12, 0x12, 0x22, 0x12, 0x22, 0x21, 0x17, 0xc6, 0x29, 0xc4, 0x1a, 0xb3, 0x5b, 0x72, 0x9c, 0x51, 0x9e, 0x71, 0x8d, 0x52, 0xab, 0x36, 0xd8, 0x29, 0xb4, 0x3b, 0xa3, 0x4b, 0xb4, 0x4b, 0xa3, 0x4c, 0x92, 0x5c, 0x92, 0x6b, 0x83, 0x8d, 0x62, 0x8c, 0x51, 0x9c, 0x51, 0xad, 0x53, 0xaa, 0x47, 0xc5, 0x2b, 0xc2, 0x3c, 0x82, 0x9c, 0x55, 0xb7, 0x29, 0xc3, 0x1a, 0xb2, 0x2a, 0xc4, 0x2a, 0xc5, 0x3a, 0xd4, 0x2a, 0xc4, 0x4b, 0x93, 0x9c, 0x53, 0xbb, 0x23, 0xca, 0x48, 0xc6, 0x4a, 0xb3, 0x3b, 0xb4, 0x5b, 0xa3, 0x3b, 0xb3, 0x3a, 0xa3, 0x3b, 0xc3, 0x2a, 0xc3, 0x3b, 0x92, 0x7c, 0x51, 0x9c, 0x42, 0xac, 0x45, 0xb8, 0x17, 0xd6, 0x18, 0xc5, 0x2b, 0xc4, 0x3b, 0xc4, 0x5c, 0x92, 0x7c, 0x72, 0x9d, 0x62, 0x8b, 0x52, 0x8c, 0x72, 0x7d, 0x92, 0x5c, 0x92, 0x6d, 0x81, 0x7d, 0x52, 0xaa, 0x35, 0xb7, 0x3a, 0xb2, 0x2b, 0xa2, 0x4c, 0x91, 0x5c, 0x82, 0x8d, 0x61, 0x9d, 0x52, 0x9a, 0x35, 0xb7, 0x17, 0xd7, 0x27, 0xc5, 0x19, 0xd4, 0x2b, 0xb2, 0x5c, 0x71, 0x8c, 0x54, 0xba, 0x35, 0xc8, 0x26, 0xd8, 0x17, 0xc5, 0x19, 0xb3, 0x3b, 0xa3, 0x5a, 0x64, 0xaa, 0x23, 0xb9, 0x27, 0xb4, 0x19, 0xb3, 0x2b, 0xa2, 0x5c, 0x73, 0x9a, 0x24, 0xc7, 0x29, 0xc3, 0x2b, 0x81, 0x6c, 0x60, 0x7d, 0x50, 0x8c, 0x43, 0xb8, 0x16, 0xc5, 0x2b, 0xb1, 0x4c, 0x81, 0x7b, 0x42, 0xba, 0x13, 0xca, 0x15, 0xd7, 0x18, 0xc4, 0x2b, 0x92, 0x7b, 0x32, 0xc9, 0x5, 0xd6, 0x2a, 0xb2, 0x4c, 0x70, 0x7d, 0x63, 0xab, 0x33, 0xba, 0x25, 0xc7, 0x17, 0xb5, 0x5b, 0x71, 0x7d, 0x63, 0xab, 0x35, 0xc7, 0x7, 0xc5, 0x2b, 0xb2, 0x4d, 0x82, 0x9c, 0x32, 0xca, 0x27, 0xc4, 0x2b, 0xa2, 0x7b, 0x44, 0xc7, 0x9, 0xc3, 0x4c, 0x71, 0x9c, 0x22, 0xc9, 0x15, 0xd8, 0x17, 0xd7, 0x39, 0x94, 0x7c, 0x61, 0x9c, 0x43, 0xba, 0x25, 0xc7, 0x3a, 0xc3, 0x2b, 0xb3, 0x5c, 0x82, 0x7c, 0x63, 0xa9, 0x27, 0xb3, 0x1c, 0xc1, 0x4d, 0x82, 0x8a, 0x35, 0xc7, 0x7, 0xe7, 0x17, 0xd7, 0x39, 0x93, 0x6c, 0x51, 0x9b, 0x22, 0xca, 0x26, 0xc6, 0x4a, 0xa3, 0x7d, 0x60, 0x9d, 0x42, 0xcb, 0x26, 0xd7, 0x3b, 0x92, 0x7b, 0x34, 0xc8, 0x29, 0x92, 0x7c, 0x53, 0xba, 0x37, 0xc6, 0x3b, 0xb2, 0x3c, 0xa3, 0x8b, 0x54, 0xb9, 0x27, 0xd6, 0x2a, 0xc4, 0x2a, 0xa4, 0x7d, 0x71, 0x7d, 0x62, 0xaa, 0x46, 0xc7, 0x18, 0xc4, 0x1a, 0xa3, 0x7d, 0x74, 0xb9, 0x38, 0xd4, 0x3c, 0xa2, 0x8d, 0x54, 0xc8, 0x3a, 0xa3, 0x8c, 0x55, 0xc7, 0x3b, 0xa3, 0x8c, 0x36, 0xf6, 0xa, 0xc3, 0x6c, 0x54, 0xb7, 0x29, 0x94, 0x8b, 0x46, 0xc5, 0x3b, 0xa2, 0x8d, 0x54, 0xc9, 0x17, 0xe7, 0x3a, 0xb4, 0x6b, 0x51, 0xaa, 0x26, 0xc5, 0x1a, 0xc2, 0x2c, 0x90, 0x6c, 0x63, 0xbb, 0x37, 0xc5, 0x4c, 0xa0, 0x5d, 0x61, 0xbc, 0x35, 0xc6, 0x2a, 0xb2, 0x4e, 0x90, 0x6d, 0x62, 0xab, 0x23, 0xb9, 0x38, 0xd5, 0x1a, 0xc3, 0x3c, 0xa3, 0x8c, 0x45, 0xd9, 0x29, 0xc2, 0x4d, 0x83, 0xbc, 0x25, 0xd6, 0x2a, 0xb3, 0x7d, 0x53, 0xca, 0x5, 0xd7, 0x19, 0xc4, 0x5d, 0x92, 0x7d, 0x63, 0xba, 0x26, 0xe8, 0x3a, 0xd4, 0x5c, 0x83, 0xbc, 0x25, 0xd7, 0x3b, 0xa2, 0x7d, 0x54, 0xc9, 0x38, 0xa4, 0x8c, 0x54, 0xc9, 0x48, 0xa5, 0x8b, 0x55, 0xb8, 0x4a, 0xa3, 0x6c, 0x73, 0xab, 0x35, 0xd9, 0x28, 0xb5, 0x6c, 0x61, 0xab, 0x25, 0xe8, 0x19, 0xd4, 0x2c, 0xa3, 0x7b, 0x55, 0xb7, 0x18, 0xc4, 0x2b, 0xa3, 0x7b, 0x64, 0xa7, 0x39, 0xb5, 0x6c, 0x73, 0x9a, 0x47, 0xa5, 0x3a, 0x81, 0x6a, 0x55, 0xb8, 0x38, 0xa2, 0x3c, 0x90, 0x5c, 0x62, 0x9a, 0x24, 0xc9, 0x48, 0xa4, 0x6c, 0x72, 0xac, 0x33, 0xa7, 0x39, 0xa3, 0x5b, 0x75, 0x98, 0x59, 0xa5, 0x6a, 0x64, 0x97, 0x27, 0xb5, 0x29, 0xa3, 0x5c, 0x83, 0x9a, 0x24, 0xb7, 0x39, 0x82, 0x7b, 0x43, 0xb8, 0x28, 0xb5, 0x5b, 0x73, 0x89, 0x46, 0xa5, 0x4b, 0x91, 0x6c, 0x61, 0x9b, 0x45, 0xb6, 0x29, 0xa3, 0x6b, 0x42, 0xba, 0x27, 0xb4, 0x3a, 0x73, 0x98, 0x48, 0x92, 0x5c, 0x51, 0xbb, 0x15, 0xc5, 0x4b, 0x81, 0x8c, 0x46, 0xc5, 0x3c, 0xa2, 0x8b, 0x34, 0xb6, 0x3a, 0x73, 0x9a, 0x37, 0xb3, 0x5c, 0x61, 0xaa, 0x38, 0xc4, 0x4c, 0x72, 0xaa, 0x15, 0xd7, 0x7, 0xc5, 0x29, 0x93, 0x7b, 0x53, 0xb9, 0x27, 0xc4, 0x3c, 0x91, 0x7c, 0x33, 0xb7, 0x38, 0x93, 0x7b, 0x33, 0xb7, 0x17, 0xc4, 0x4b, 0x83, 0x8a, 0x34, 0xb9, 0x26, 0xb5, 0x19, 0xb3, 0x2b, 0xa2, 0x6c, 0x40, 0xaa, 0x15, 0xb5, 0x3a, 0x71, 0x79, 0x24, 0xc7, 0x29, 0xa1, 0x3a, 0x61, 0x8a, 0x12, 0xa7, 0x17, 0xa3, 0x4b, 0x71, 0x8a, 0x13, 0xa6, 0x28, 0x73, 0x79, 0x45, 0x95, 0x3a, 0x81, 0x5a, 0x31, 0x99, 0x24, 0xa5, 0x17, 0x82, 0x4a, 0x60, 0x6a, 0x31, 0xaa, 0x13, 0xb7, 0x6, 0xb3, 0x8, 0x81, 0x5a, 0x52, 0x98, 0x13, 0xb7, 0x15, 0xb5, 0x6, 0xa4, 0x19, 0xa1, 0x2a, 0x61, 0x79, 0x34, 0x94, 0x18, 0x81, 0x5a, 0x43, 0x96, 0x27, 0x83, 0x58, 0x44, 0x95, 0x38, 0x72, 0x68, 0x35, 0x85, 0x48, 0x53, 0x78, 0x35, 0x94, 0x16, 0x93, 0x19, 0xa2, 0x2a, 0x80, 0x5a, 0x32, 0xa6, 0x7, 0xa2, 0x2b, 0x80, 0x5b, 0x51, 0x8a, 0x12, 0x97, 0x27, 0x83, 0x59, 0x42, 0x98, 0x14, 0xb6, 0x17, 0xb4, 0x18, 0x93, 0x49, 0x71, 0x5a, 0x61, 0x69, 0x33, 0xa6, 0x6, 0xa3, 0x1a, 0x82, 0x59, 0x43, 0x85, 0x39, 0x71, 0x5a, 0x52, 0x98, 0x26, 0x84, 0x59, 0x53, 0x86, 0x6, 0xa3, 0x3a, 0x61, 0x78, 0x35, 0x74, 0x58, 0x54, 0x86, 0x27, 0x83, 0x38, 0x61, 0x4a, 0x61, 0x6a, 0x41, 0x89, 0x35, 0x94, 0x29, 0x82, 0x59, 0x44, 0x94, 0x19, 0x91, 0x5b, 0x30, 0x98, 0x16, 0x93, 0x49, 0x53, 0x86, 0x17, 0x93, 0x49, 0x41, 0x89, 0x23, 0xa7, 0x26, 0x84, 0x48, 0x52, 0x78, 0x25, 0xa5, 0x18, 0x92, 0x49, 0x53, 0x86, 0x27, 0x81, 0x29, 0x62, 0x77, 0x26, 0x82, 0x3a, 0x50, 0x7a, 0x22, 0x96, 0x15, 0xa4, 0x27, 0x71, 0x49, 0x52, 0x78, 0x24, 0x95, 0x17, 0x81, 0x28, 0x62, 0x77, 0x24, 0x95, 0x16, 0x93, 0x17, 0x82, 0x28, 0x61, 0x59, 0x51, 0x79, 0x22, 0x87, 0x25, 0x82, 0x28, 0x70, 0x49, 0x41, 0x77, 0x24, 0x95, 0x27, 0x61, 0x59, 0x32, 0x87, 0x4, 0x84, 0x37, 0x63, 0x66, 0x25, 0x83, 0x28, 0x71, 0x49, 0x52, 0x68, 0x31, 0x78, 0x34, 0x86, 0x26, 0x83, 0x38, 0x70, 0x39, 0x62, 0x66, 0x24, 0x83, 0x27, 0x72, 0x57, 0x44, 0x74, 0x28, 0x81, 0x39, 0x61, 0x68, 0x12, 0x96, 0x5, 0x94, 0x37, 0x63, 0x67, 0x35, 0x63, 0x48, 0x41, 0x68, 0x21, 0x77, 0x22, 0x87, 0x24, 0x85, 0x27, 0x61, 0x48, 0x42, 0x76, 0x15, 0x94, 0x27, 0x62, 0x58, 0x21, 0x87, 0x14, 0x83, 0x7, 0x82, 0x48, 0x53, 0x65, 0x27, 0x71, 0x39, 0x51, 0x68, 0x34, 0x75, 0x37, 0x51, 0x58, 0x31, 0x78, 0x22, 0x87, 0x26, 0x73, 0x47, 0x53, 0x76, 0x36, 0x63, 0x57, 0x44, 0x74, 0x16, 0x93, 0x17, 0x73, 0x58, 0x41, 0x68, 0x34, 0x85, 0x15, 0x94, 0x37, 0x53, 0x67, 0x23, 0x86, 0x15, 0x83, 0x27, 0x71, 0x38, 0x51, 0x68, 0x33, 0x76, 0x36, 0x72, 0x39, 0x50, 0x58, 0x34, 0x85, 0x36, 0x63, 0x67, 0x23, 0x85, 0x5, 0x83, 0x17, 0x62, 0x47, 0x43, 0x65, 0x25, 0x73, 0x37, 0x61, 0x58, 0x43, 0x76, 0x13, 0x85, 0x15, 0x73, 0x27, 0x62, 0x48, 0x42, 0x76, 0x15, 0x73, 0x37, 0x42, 0x66, 0x24, 0x74, 0x37, 0x52, 0x66, 0x24, 0x83, 0x16, 0x71, 0x28, 0x61, 0x48, 0x42, 0x66, 0x24, 0x83, 0x16, 0x72, 0x28, 0x51, 0x57, 0x22, 0x75, 0x14, 0x72, 0x37, 0x40, 0x57, 0x22, 0x86, 0x15, 0x83, 0x27, 0x61, 0x38, 0x52, 0x68, 0x32, 0x86, 0x14, 0x95, 0x16, 0x83, 0x38, 0x61, 0x58, 0x33, 0x75, 0x26, 0x62, 0x57, 0x33, 0x85, 0x15, 0x73, 0x48, 0x41, 0x67, 0x24, 0x74, 0x26, 0x62, 0x38, 0x51, 0x57, 0x22, 0x75, 0x25, 0x62, 0x37, 0x32, 0x76, 0x3, 0x73, 0x37, 0x52, 0x56, 0x24, 0x73, 0x16, 0x61, 0x37, 0x43, 0x65, 0x25, 0x73, 0x36, 0x42, 0x55, 0x25, 0x72, 0x27, 0x41, 0x67, 0x23, 0x75, 0x5, 0x82, 0x17, 0x61, 0x47, 0x32, 0x65, 0x15, 0x72, 0x27, 0x41, 0x57, 0x22, 0x76, 0x13, 0x74, 0x14, 0x74, 0x15, 0x72, 0x16, 0x62, 0x46, 0x22, 0x65, 0x24, 0x62, 0x37, 0x31, 0x57, 0x22, 0x75, 0x15, 0x73, 0x26, 0x52, 0x47, 0x31, 0x57, 0x32, 0x65, 0x25, 0x63, 0x37, 0x41, 0x58, 0x31, 0x77, 0x23, 0x74, 0x15, 0x62, 0x47, 0x43, 0x65, 0x35, 0x62, 0x37, 0x52, 0x47, 0x42, 0x67, 0x33, 0x75, 0x15, 0x84, 0x37, 0x52, 0x66, 0x13, 0x84, 0x26, 0x61, 0x48, 0x32, 0x75, 0x15, 0x73, 0x37, 0x52, 0x67, 0x23, 0x74, 0x26, 0x63, 0x47, 0x52, 0x57, 0x32, 0x66, 0x34, 0x64, 0x36, 0x52, 0x47, 0x42, 0x66, 0x35, 0x63, 0x47, 0x42, 0x57, 0x34, 0x74, 0x36, 0x63, 0x56, 0x34, 0x65, 0x45, 0x44, 0x66, 0x35, 0x73, 0x26, 0x62, 0x37, 0x53, 0x57, 0x33, 0x75, 0x25, 0x74, 0x36, 0x53, 0x55, 0x24, 0x63, 0x36, 0x52, 0x47, 0x42, 0x57, 0x32, 0x56, 0x33, 0x66, 0x23, 0x65, 0x35, 0x62, 0x26, 0x52, 0x36, 0x42, 0x56, 0x32, 0x65, 0x34, 0x63, 0x27, 0x61, 0x37, 0x31, 0x56, 0x24, 0x64, 0x36, 0x52, 0x47, 0x32, 0x65, 0x24, 0x74, 0x26, 0x72, 0x27, 0x52, 0x46, 0x43, 0x65, 0x24, 0x73, 0x25, 0x62, 0x26, 0x52, 0x35, 0x43, 0x54, 0x25, 0x62, 0x26, 0x42, 0x46, 0x33, 0x64, 0x15, 0x62, 0x26, 0x52, 0x46, 0x31, 0x56, 0x12, 0x65, 0x25, 0x53, 0x45, 0x34, 0x63, 0x26, 0x51, 0x37, 0x41, 0x47, 0x42, 0x55, 0x23, 0x65, 0x25, 0x63, 0x36, 0x41, 0x46, 0x42, 0x57, 0x32, 0x56, 0x22, 0x65, 0x14, 0x63, 0x26, 0x51, 0x37, 0x41, 0x56, 0x24, 0x53, 0x26, 0x51, 0x36, 0x32, 0x56, 0x22, 0x66, 0x23, 0x63, 0x25, 0x52, 0x46, 0x31, 0x55, 0x24, 0x63, 0x25, 0x43, 0x55, 0x24, 0x63, 0x15, 0x62, 0x36, 0x42, 0x55, 0x23, 0x53, 0x26, 0x51, 0x36, 0x31, 0x55, 0x23, 0x63, 0x25, 0x52, 0x45, 0x33, 0x54, 0x24, 0x52, 0x25, 0x42, 0x44, 0x34, 0x52, 0x35, 0x42, 0x55, 0x23, 0x64, 0x25, 0x52, 0x36, 0x31, 0x45, 0x23, 0x54, 0x14, 0x52, 0x15, 0x51, 0x36, 0x31, 0x45, 0x23, 0x53, 0x35, 0x32, 0x43, 0x25, 0x51, 0x35, 0x32, 0x54, 0x24, 0x53, 0x25, 0x51, 0x26, 0x41, 0x45, 0x32, 0x54, 0x13, 0x52, 0x25, 0x42, 0x45, 0x23, 0x53, 0x25, 0x42, 0x45, 0x22, 0x55, 0x24, 0x52, 0x35, 0x32, 0x44, 0x23, 0x53, 0x14, 0x52, 0x36, 0x31, 0x45, 0x22, 0x54, 0x24, 0x52, 0x25, 0x31, 0x45, 0x22, 0x54, 0x23, 0x64, 0x23, 0x53, 0x24, 0x53, 0x25, 0x42, 0x34, 0x33, 0x53, 0x25, 0x52, 0x35, 0x32, 0x54, 0x14, 0x52, 0x26, 0x41, 0x45, 0x23, 0x53, 0x24, 0x42, 0x45, 0x24, 0x53, 0x36, 0x31, 0x55, 0x23, 0x63, 0x14, 0x52, 0x25, 0x42, 0x35, 0x33, 0x43, 0x35, 0x42, 0x45, 0x22, 0x54, 0x13, 0x63, 0x15, 0x51, 0x26, 0x41, 0x45, 0x23, 0x53, 0x25, 0x41, 0x45, 0x23, 0x53, 0x25, 0x32, 0x55, 0x23, 0x62, 0x15, 0x52, 0x35, 0x32, 0x54, 0x23, 0x53, 0x25, 0x42, 0x45, 0x22, 0x54, 0x24, 0x51, 0x36, 0x31, 0x45, 0x23, 0x53, 0x25, 0x32, 0x55, 0x13, 0x53, 0x24, 0x32, 0x45, 0x23, 0x42, 0x35, 0x31, 0x55, 0x23, 0x52, 0x15, 0x41, 0x35, 0x32, 0x45, 0x23, 0x54, 0x24, 0x63, 0x24, 0x52, 0x35, 0x31, 0x45, 0x23, 0x53, 0x14, 0x52, 0x25, 0x41, 0x35, 0x32, 0x53, 0x24, 0x42, 0x35, 0x22, 0x54, 0x13, 0x63, 0x14, 0x52, 0x25, 0x52, 0x35, 0x32, 0x54, 0x23, 0x52, 0x15, 0x41, 0x25, 0x32, 0x44, 0x12, 0x54, 0x13, 0x52, 0x25, 0x42, 0x35, 0x22, 0x53, 0x13, 0x42, 0x35, 0x31, 0x44, 0x23, 0x42, 0x24, 0x42, 0x34, 0x21, 0x44, 0x11, 0x54, 0x12, 0x53, 0x13, 0x52, 0x24, 0x32, 0x44, 0x12, 0x43, 0x24, 0x31, 0x35, 0x21, 0x44, 0x23, 0x42, 0x24, 0x31, 0x35, 0x22, 0x44, 0x12, 0x43, 0x23, 0x42, 0x24, 0x31, 0x35, 0x22, 0x44, 0x23, 0x42, 0x24, 0x41, 0x35, 0x22, 0x43, 0x23, 0x42, 0x34, 0x32, 0x44, 0x23, 0x43, 0x23, 0x42, 0x24, 0x42, 0x25, 0x32, 0x35, 0x32, 0x43, 0x23, 0x32, 0x35, 0x22, 0x53, 0x13, 0x42, 0x24, 0x32, 0x43, 0x24, 0x41, 0x25, 0x32, 0x43, 0x24, 0x42, 0x25, 0x31, 0x34, 0x22, 0x44, 0x22, 0x43, 0x23, 0x43, 0x24, 0x32, 0x34, 0x23, 0x53, 0x24, 0x42, 0x35, 0x22, 0x53, 0x14, 0x52, 0x25, 0x42, 0x34, 0x22, 0x43, 0x23, 0x42, 0x24, 0x32, 0x34, 0x22, 0x44, 0x23, 0x42, 0x24, 0x32, 0x35, 0x21, 0x44, 0x22, 0x43, 0x23, 0x42, 0x14, 0x42, 0x35, 0x31, 0x44, 0x12, 0x53, 0x13, 0x42, 0x25, 0x32, 0x44, 0x23, 0x52, 0x13, 0x42, 0x24, 0x31, 0x24, 0x32, 0x34, 0x21, 0x34, 0x22, 0x42, 0x24, 0x32, 0x33, 0x22, 0x42, 0x24, 0x31, 0x24, 0x22, 0x43, 0x24, 0x41, 0x24, 0x22, 0x43, 0x24, 0x32, 0x34, 0x22, 0x42, 0x24, 0x31, 0x35, 0x22, 0x43, 0x23, 0x42, 0x13, 0x42, 0x14, 0x42, 0x24, 0x22, 0x43, 0x13, 0x42, 0x24, 0x32, 0x34, 0x12, 0x43, 0x23, 0x32, 0x34, 0x21, 0x34, 0x22, 0x43, 0x22, 0x43, 0x22, 0x43, 0x22, 0x43, 0x23, 0x42, 0x24, 0x31, 0x34, 0x22, 0x43, 0x23, 0x42, 0x24, 0x31, 0x34, 0x21, 0x33, 0x22, 0x43, 0x23, 0x32, 0x24, 0x21, 0x34, 0x22, 0x43, 0x23, 0x42, 0x13, 0x32, 0x34, 0x22, 0x43, 0x13, 0x42, 0x24, 0x21, 0x34, 0x22, 0x43, 0x13, 0x42, 0x24, 0x31, 0x24, 0x21, 0x34, 0x22, 0x43, 0x23, 0x42, 0x24, 0x32, 0x34, 0x22, 0x43, 0x13, 0x42, 0x24, 0x31, 0x34, 0x12, 0x43, 0x13, 0x41, 0x14, 0x32, 0x34, 0x21, 0x44, 0x22, 0x43, 0x23, 0x42, 0x23, 0x42, 0x24, 0x31, 0x24, 0x32, 0x24, 0x32, 0x33, 0x22, 0x42, 0x23, 0x32, 0x24, 0x22, 0x33, 0x13, 0x42, 0x14, 0x32, 0x34, 0x22, 0x43, 0x22, 0x42, 0x23, 0x42, 0x24, 0x31, 0x24, 0x22, 0x33, 0x22, 0x42, 0x13, 0x42, 0x24, 0x31, 0x24, 0x21, 0x33, 0x22, 0x43, 0x12, 0x42, 0x13, 0x42, 0x24, 0x32, 0x33, 0x22, 0x32, 0x23, 0x31, 0x24, 0x21, 0x34, 0x22, 0x42, 0x13, 0x42, 0x23, 0x32, 0x23, 0x22, 0x33, 0x22, 0x32, 0x13, 0x42, 0x23, 0x31, 0x24, 0x22, 0x33, 0x12, 0x42, 0x13, 0x32, 0x24, 0x22, 0x43, 0x12, 0x42, 0x23, 0x32, 0x24, 0x31, 0x24, 0x31, 0x24, 0x22, 0x33, 0x13, 0x32, 0x23, 0x22, 0x33, 0x23, 0x31, 0x24, 0x31, 0x23, 0x22, 0x33, 0x22, 0x42, 0x13, 0x32, 0x23, 0x21, 0x33, 0x22, 0x33, 0x13, 0x32, 0x23, 0x32, 0x33, 0x22, 0x33, 0x12, 0x43, 0x12, 0x43, 0x12, 0x42, 0x13, 0x42, 0x13, 0x32, 0x23, 0x22, 0x33, 0x22, 0x32, 0x23, 0x31, 0x23, 0x22, 0x33, 0x12, 0x32, 0x13, 0x32, 0x23, 0x31, 0x23, 0x32, 0x33, 0x22, 0x32, 0x23, 0x32, 0x23, 0x22, 0x33, 0x12, 0x42, 0x13, 0x32, 0x23, 0x21, 0x24, 0x21, 0x33, 0x12, 0x33, 0x23, 0x32, 0x23, 0x32, 0x33, 0x23, 0x32, 0x23, 0x31, 0x33, 0x12, 0x43, 0x23, 0x32, 0x23, 0x22, 0x33, 0x12, 0x42, 0x23, 0x42, 0x24, 0x32, 0x24, 0x21, 0x34, 0x22, 0x33, 0x23, 0x32, 0x24, 0x31, 0x34, 0x22, 0x33, 0x22, 0x43, 0x12, 0x32, 0x12, 0x32, 0x13, 0x32, 0x23, 0x32, 0x23, 0x21, 0x33, 0x22, 0x32, 0x13, 0x32, 0x23, 0x32, 0x33, 0x22, 0x33, 0x12, 0x42, 0x23, 0x32, 0x23, 0x21, 0x23, 0x21, 0x33, 0x22, 0x32, 0x23, 0x32, 0x23, 0x22, 0x32, 0x13, 0x32, 0x23, 0x21, 0x33, 0x21, 0x33, 0x12, 0x32, 0x12, 0x32, 0x23, 0x21, 0x33, 0x21, 0x33, 0x12, 0x32, 0x12, 0x32, 0x23, 0x32, 0x33, 0x22, 0x32, 0x13, 0x32, 0x23, 0x21, 0x33, 0x22, 0x32, 0x23, 0x31, 0x23, 0x31, 0x23, 0x21, 0x33, 0x21, 0x33, 0x22, 0x33, 0x12, 0x32, 0x13, 0x32, 0x23, 0x22, 0x32, 0x12, 0x32, 0x13, 0x32, 0x23, 0x21, 0x33, 0x22, 0x32, 0x23, 0x32, 0x23, 0x22, 0x32, 0x12, 0x31, 0x13, 0x21, 0x23, 0x22, 0x32, 0x12, 0x32, 0x12, 0x32, 0x23, 0x21, 0x23, 0x22, 0x23, 0x22, 0x32, 0x12, 0x32, 0x23, 0x21, 0x23, 0x21, 0x23, 0x22, 0x33, 0x12, 0x32, 0x12, 0x32, 0x23, 0x22, 0x32, 0x12, 0x31, 0x23, 0x21, 0x23, 0x21, 0x33, 0x22, 0x32, 0x12, 0x32, 0x23, 0x21, 0x23, 0x21, 0x33, 0x22, 0x32, 0x12, 0x32, 0x12, 0x32, 0x23, 0x21, 0x23, 0x22, 0x33, 0x22, 0x32, 0x12, 0x32, 0x23, 0x22, 0x23, 0x21, 0x32, 0x12, 0x32, 0x23, 0x32, 0x23, 0x21, 0x23, 0x22, 0x23, 0x22, 0x32, 0x12, 0x32, 0x13, 0x22, 0x23, 0x22, 0x32, 0x23, 0x22, 0x33, 0x12, 0x32, 0x12, 0x32, 0x23, 0x22, 0x32, 0x22, 0x32, 0x23, 0x21, 0x23, 0x21, 0x33, 0x22, 0x32, 0x13, 0x31, 0x23, 0x22, 0x33, 0x12, 0x32, 0x12, 0x32, 0x23, 0x21, 0x23, 0x21, 0x23, 0x12, 0x32, 0x12, 0x32, 0x12, 0x32, 0x13, 0x32, 0x13, 0x32, 0x23, 0x21, 0x23, 0x22, 0x33, 0x12, 0x32, 0x22, 0x32, 0x22, 0x32, 0x22, 0x32, 0x22, 0x22, 0x22, 0x12, 0x32, 0x23, 0x32, 0x23, 0x22, 0x32, 0x12, 0x32, 0x13, 0x21, 0x23, 0x12, 0x32, 0x22, 0x21, 0x23, 0x22, 0x33, 0x22, 0x32, 0x23, 0x21, 0x23, 0x21, 0x23, 0x22, 0x22, 0x12, 0x32, 0x12, 0x32, 0x12, 0x31, 0x23, 0x21, 0x33, 0x12, 0x32, 0x23, 0x22, 0x22, 0x22, 0x32, 0x23, 0x21, 0x23, 0x22, 0x22, 0x22, 0x32, 0x12, 0x32, 0x22, 0x32, 0x12, 0x32, 0x13, 0x31, 0x23, 0x21, 0x23, 0x22, 0x32, 0x22, 0x22, 0x23, 0x21, 0x23, 0x12, 0x32, 0x23, 0x22, 0x23, 0x21, 0x23, 0x21, 0x33, 0x22, 0x32, 0x23, 0x21, 0x23, 0x21, 0x32, 0x12, 0x32, 0x22, 0x32, 0x23, 0x21, 0x23, 0x22, 0x33, 0x22, 0x32, 0x12, 0x32, 0x22, 0x22, 0x22, 0x22, 0x32, 0x12, 0x32, 0x12, 0x32, 0x23, 0x21, 0x23, 0x21, 0x23, 0x21, 0x32, 0x12, 0x32, 0x13, 0x22, 0x23, 0x21, 0x32, 0x12, 0x32, 0x22, 0x21, 0x22, 0x22, 0x32, 0x22, 0x21, 0x23, 0x21, 0x22, 0x22, 0x32, 0x12, 0x21, 0x23, 0x21, 0x23, 0x22, 0x22, 0x12, 0x32, 0x22, 0x21, 0x23, 0x21, 0x23, 0x22, 0x32, 0x12, 0x32, 0x12, 0x32, 0x12, 0x22, 0x12, 0x21, 0x23, 0x21, 0x23, 0x22, 0x22, 0x22, 0x32, 0x12, 0x21, 0x23, 0x21, 0x23, 0x22, 0x32, 0x12, 0x22, 0x23, 0x22, 0x22, 0x12, 0x32, 0x22, 0x21, 0x23, 0x21, 0x23, 0x21, 0x23, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x32, 0x12, 0x21, 0x23, 0x21, 0x23, 0x21, 0x22, 0x12, 0x32, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x32, 0x12, 0x22, 0x22, 0x21, 0x22, 0x22, 0x32, 0x22, 0x21, 0x23, 0x22, 0x22, 0x11, 0x22, 0x12, 0x32, 0x12, 0x22, 0x22, 0x21, 0x22, 0x22, 0x32, 0x12, 0x21, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x32, 0x22, 0x22, 0x23, 0x22, 0x32, 0x22, 0x32, 0x22, 0x22, 0x22, 0x22, 0x23, 0x21, 0x23, 0x22, 0x22, 0x22, 0x22, 0x23, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x32, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x23, 0x21, 0x22, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x21, 0x23, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x23, 0x21, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x22, 0x23, 0x21, 0x22, 0x21, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x21, 0x23, 0x21, 0x22, 0x22, 0x22, 0x12, 0x21, 0x23, 0x21, 0x23, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x12, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x21, 0x22, 0x12, 0x22, 0x12, 0x21, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x11, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x12, 0x21, 0x22, 0x21, 0x22, 0x11, 0x22, 0x12, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x21, 0x12, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x21, 0x12, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x22, 0x12, 0x21, 0x22, 0x21, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x12, 0x20, };
	
unsigned char (*g_soundArray)[];
unsigned long g_soundIndex;
unsigned long g_soundMax;

void SoundInit(void) {
	DACInit();
	Timer0AInit(PlaySound, 1000000/8000);
}

void PlaySound(void) {
	if (g_soundArray != 0) {
		if (g_soundIndex >= g_soundMax*2) {
			g_soundArray = 0;
		} else {
			if ((g_soundIndex%2) == 0) {
				DACOut(((*g_soundArray)[g_soundIndex/2]&0xF0)>>4);
			} else {
				DACOut((*g_soundArray)[g_soundIndex/2]&0x0F);
			}
			g_soundIndex++;
		}
	}
}
