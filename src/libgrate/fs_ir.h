#include <stdint.h>

enum fs_alu_op {
	FS_OP_MAD = 0,
	FS_OP_MIN = 1,
	FS_OP_MAX = 2,
	FS_OP_CND = 3
};

enum fs_pred {
	FS_PRED_Z = 0,
	FS_PRED_NZ = 1,
	FS_PRED_LE = 2,
	FS_PRED_LT = 3
};

enum fs_subreg_mask {
	FS_SUBREG_NONE = 0,
	FS_SUBREG_LOW = 1,
	FS_SUBREG_HIGH = 2,
	FS_SUBREG_BOTH = 3
};

enum fs_src_type {
	FS_SRC_GPR = 0,
	FS_SRC_CONST = 1,
	FS_SRC_SYSTEM = 2
};

enum fs_dst_scale {
	DST_SCALE_ONE,
	DST_SCALE_MUL2,
	DST_SCALE_MUL4,
	DST_SCALE_DIV2
};

struct fs_alu_dst {
	int reg;
	enum fs_subreg_mask subreg;
	enum fs_pred pred;
	enum fs_dst_scale scale;
	unsigned char sat : 1,
	              accum : 1,
	              use_pred : 1;
};

struct fs_alu_src {
	enum fs_src_type type;
	int reg;
	unsigned char x10 : 1,
	              subreg : 1,
	              abs : 1,
	              neg : 1,
	              mul2 : 1;
};

struct fs_alu_instr {
	enum fs_alu_op opcode;
	struct fs_alu_dst dst;
	struct fs_alu_src src[3];
};

uint64_t fs_alu_encode(const struct fs_alu_instr *);
