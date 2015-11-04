#include "fs_ir.h"

uint64_t fs_alu_encode(const struct fs_alu_instr *instr)
{
	int i;
	uint64_t result = 0;

	result |= (uint64_t)instr->opcode << 62;

	result |= (uint64_t)instr->dst.accum << 61;
	result |= (uint64_t)instr->dst.scale << 58;
	result |= (uint64_t)instr->dst.sat << 56;

	if (instr->dst.use_pred)
		result |= (1ULL << 53) | ((uint64_t)instr->dst.pred << 54);

	result |= (uint64_t)instr->dst.reg << 47;
	result |= (uint64_t)instr->dst.subreg << 45;

	for (i = 0; i < 3; ++i) {
		const struct fs_alu_src *src = instr->src + i;
		uint32_t tmp = 0;
		tmp |= src->reg << 6;
		tmp |= src->subreg << 5;
		tmp |= src->x10 << 3;
		tmp |= src->abs << 2;
		tmp |= src->neg << 1;
		tmp |= src->mul2;
		result |= tmp << (32 - 13 * i);
	}

#if 0
	/* one final bastard operand:
	 * rD, sourced from one of the other
	 */
	result |= instr->dst.rd_sel << 4;
	result |= instr->dst.rc_mul_rd << 2;
	result |= instr->dst.rd_abs << 1;
#endif

	return result;
}
