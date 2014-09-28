#include "stdafx.h"
#include "r3051.h"

#define op_impl(name) static void r3051_stage_dc_##name(struct r3051*, struct r3051_stage*)
#define op_decl(name) static void r3051_stage_dc_##name(struct r3051* processor, struct r3051_stage* stage)
#define op_call(name) r3051_stage_dc_##name(processor, stage)

op_impl(lb);
op_impl(lbu);
op_impl(lh);
op_impl(lhu);
op_impl(lw);
op_impl(sb);
op_impl(sh);
op_impl(sw);

void r3051_stage_dc(struct r3051* processor) {
  struct r3051_stage* stage = &processor->dc;

  switch (stage->op) {
  case 0x00: return;
  case 0x01: return;
  case 0x02: return; // j
  case 0x03: return; // jal
  case 0x04: return; // beq
  case 0x05: return; // bne
  case 0x06: return; // blez
  case 0x07: return; // bgtz
  case 0x08: return; // addi
  case 0x09: return; // addiu
  case 0x0a: return; // slti
  case 0x0b: return; // sltiu
  case 0x0c: return; // andi
  case 0x0d: return; // ori

  case 0x0f: return; // lui
  case 0x10: return; // cop0

  case 0x20: op_call(lb); return; // lb
  case 0x21: op_call(lh); return; // lh

  case 0x23: op_call(lw); return; // lw
  case 0x24: op_call(lbu); return; // lbu
  case 0x25: op_call(lhu); return; // lhu

  case 0x28: op_call(sb); return; // sb
  case 0x29: op_call(sh); return; // sh

  case 0x2b: op_call(sw); return; // sw
  }

  assert(0 && "Unimplemented instruction");
}

op_decl(lb) {
  processor->registers[stage->rt] = r3051_fetch_byte(stage->target);
}

op_decl(lbu) {
  processor->registers[stage->rt] = r3051_fetch_byte(stage->target) & 0xff;
}

op_decl(lh) {
	processor->registers[stage->rt] = r3051_fetch_half(stage->target);
}

op_decl(lhu) {
	processor->registers[stage->rt] = r3051_fetch_half(stage->target) & 0xffff;
}

op_decl(lw) {
  processor->registers[stage->rt] = r3051_fetch_word(stage->target);
}

op_decl(sb) {
  r3051_store_byte(stage->target, processor->registers[stage->rt]);
}

op_decl(sh) {
  r3051_store_half(stage->target, processor->registers[stage->rt]);
}

op_decl(sw) {
  r3051_store_word(stage->target, processor->registers[stage->rt]);
}
