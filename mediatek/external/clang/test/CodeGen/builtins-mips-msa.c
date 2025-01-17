// REQUIRES: mips-registered-target
// RUN: %clang_cc1 -triple mips-unknown-linux-gnu -emit-llvm %s -o - \
// RUN:   | FileCheck %s

typedef signed char      v16i8 __attribute__ ((vector_size(16)));
typedef signed short     v8i16 __attribute__ ((vector_size(16)));
typedef signed int       v4i32 __attribute__ ((vector_size(16)));
typedef signed long long v2i64 __attribute__ ((vector_size(16)));
typedef unsigned char      v16u8 __attribute__ ((vector_size(16)));
typedef unsigned short     v8u16 __attribute__ ((vector_size(16)));
typedef unsigned int       v4u32 __attribute__ ((vector_size(16)));
typedef unsigned long long v2u64 __attribute__ ((vector_size(16)));
typedef __fp16 v8f16 __attribute__ ((vector_size(16)));
typedef float  v4f32 __attribute__ ((vector_size(16)));
typedef double v2f64 __attribute__ ((vector_size(16)));

void test(void) {
  v16i8 v16i8_a = (v16i8) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  v16i8 v16i8_b = (v16i8) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  v16i8 v16i8_r;
  v8i16 v8i16_a = (v8i16) {0, 1, 2, 3, 4, 5, 6, 7};
  v8i16 v8i16_b = (v8i16) {1, 2, 3, 4, 5, 6, 7, 8};
  v8i16 v8i16_r;
  v4i32 v4i32_a = (v4i32) {0, 1, 2, 3};
  v4i32 v4i32_b = (v4i32) {1, 2, 3, 4};
  v4i32 v4i32_r;
  v2i64 v2i64_a = (v2i64) {0, 1};
  v2i64 v2i64_b = (v2i64) {1, 2};
  v2i64 v2i64_r;

  v16u8 v16u8_a = (v16u8) {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  v16u8 v16u8_b = (v16u8) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  v16u8 v16u8_r;
  v8u16 v8u16_a = (v8u16) {0, 1, 2, 3, 4, 5, 6, 7};
  v8u16 v8u16_b = (v8u16) {1, 2, 3, 4, 5, 6, 7, 8};
  v8u16 v8u16_r;
  v4u32 v4u32_a = (v4u32) {0, 1, 2, 3};
  v4u32 v4u32_b = (v4u32) {1, 2, 3, 4};
  v4u32 v4u32_r;
  v2u64 v2u64_a = (v2u64) {0, 1};
  v2u64 v2u64_b = (v2u64) {1, 2};
  v2u64 v2u64_r;

  v8f16 v8f16_a = (v8f16) {0.5, 1, 2, 3, 4, 5, 6, 7};
  v8f16 v8f16_b = (v8f16) {1.5, 2, 3, 4, 5, 6, 7, 8};
  v8f16 v8f16_r;
  v4f32 v4f32_a = (v4f32) {0.5, 1, 2, 3};
  v4f32 v4f32_b = (v4f32) {1.5, 2, 3, 4};
  v4f32 v4f32_r;
  v2f64 v2f64_a = (v2f64) {0.5, 1};
  v2f64 v2f64_b = (v2f64) {1.5, 2};
  v2f64 v2f64_r;

  int int_r;
  int int_a = 0;

  v16i8_r = __builtin_msa_add_a_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.add.a.b(
  v8i16_r = __builtin_msa_add_a_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.add.a.h(
  v4i32_r = __builtin_msa_add_a_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.add.a.w(
  v2i64_r = __builtin_msa_add_a_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.add.a.d(

  v16i8_r = __builtin_msa_adds_a_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.adds.a.b(
  v8i16_r = __builtin_msa_adds_a_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.adds.a.h(
  v4i32_r = __builtin_msa_adds_a_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.adds.a.w(
  v2i64_r = __builtin_msa_adds_a_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.adds.a.d(

  v16i8_r = __builtin_msa_adds_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.adds.s.b(
  v8i16_r = __builtin_msa_adds_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.adds.s.h(
  v4i32_r = __builtin_msa_adds_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.adds.s.w(
  v2i64_r = __builtin_msa_adds_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.adds.s.d(

  v16u8_r = __builtin_msa_adds_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.adds.u.b(
  v8u16_r = __builtin_msa_adds_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.adds.u.h(
  v4u32_r = __builtin_msa_adds_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.adds.u.w(
  v2u64_r = __builtin_msa_adds_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.adds.u.d(

  v16i8_r = __builtin_msa_addv_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.addv.b(
  v8i16_r = __builtin_msa_addv_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.addv.h(
  v4i32_r = __builtin_msa_addv_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.addv.w(
  v2i64_r = __builtin_msa_addv_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.addv.d(

  v16u8_r = __builtin_msa_addv_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.addv.b(
  v8u16_r = __builtin_msa_addv_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.addv.h(
  v4u32_r = __builtin_msa_addv_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.addv.w(
  v2u64_r = __builtin_msa_addv_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.addv.d(

  v16i8_r = __builtin_msa_addvi_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.addvi.b(
  v8i16_r = __builtin_msa_addvi_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.addvi.h(
  v4i32_r = __builtin_msa_addvi_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.addvi.w(
  v2i64_r = __builtin_msa_addvi_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.addvi.d(

  v16u8_r = __builtin_msa_addvi_b(v16u8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.addvi.b(
  v8u16_r = __builtin_msa_addvi_h(v8u16_a, 25); // CHECK: call <8  x i16> @llvm.mips.addvi.h(
  v4u32_r = __builtin_msa_addvi_w(v4u32_a, 25); // CHECK: call <4  x i32> @llvm.mips.addvi.w(
  v2u64_r = __builtin_msa_addvi_d(v2u64_a, 25); // CHECK: call <2  x i64> @llvm.mips.addvi.d(

  v16i8_r = __builtin_msa_andi_b(v16i8_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(
  v8i16_r = __builtin_msa_andi_b(v8i16_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(
  v4i32_r = __builtin_msa_andi_b(v4i32_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(
  v2i64_r = __builtin_msa_andi_b(v2i64_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(

  v16u8_r = __builtin_msa_andi_b(v16u8_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(
  v8u16_r = __builtin_msa_andi_b(v8u16_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(
  v4u32_r = __builtin_msa_andi_b(v4u32_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(
  v2u64_r = __builtin_msa_andi_b(v2u64_a, 25); // CHECK: call <16 x i8> @llvm.mips.andi.b(

  v16i8_r = __builtin_msa_asub_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.asub.s.b(
  v8i16_r = __builtin_msa_asub_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.asub.s.h(
  v4i32_r = __builtin_msa_asub_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.asub.s.w(
  v2i64_r = __builtin_msa_asub_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.asub.s.d(

  v16u8_r = __builtin_msa_asub_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.asub.u.b(
  v8u16_r = __builtin_msa_asub_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.asub.u.h(
  v4u32_r = __builtin_msa_asub_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.asub.u.w(
  v2u64_r = __builtin_msa_asub_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.asub.u.d(

  v16i8_r = __builtin_msa_ave_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.ave.s.b(
  v8i16_r = __builtin_msa_ave_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.ave.s.h(
  v4i32_r = __builtin_msa_ave_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.ave.s.w(
  v2i64_r = __builtin_msa_ave_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.ave.s.d(

  v16u8_r = __builtin_msa_ave_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.ave.u.b(
  v8u16_r = __builtin_msa_ave_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.ave.u.h(
  v4u32_r = __builtin_msa_ave_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.ave.u.w(
  v2u64_r = __builtin_msa_ave_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.ave.u.d(

  v16i8_r = __builtin_msa_aver_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.aver.s.b(
  v8i16_r = __builtin_msa_aver_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.aver.s.h(
  v4i32_r = __builtin_msa_aver_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.aver.s.w(
  v2i64_r = __builtin_msa_aver_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.aver.s.d(

  v16u8_r = __builtin_msa_aver_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.aver.u.b(
  v8u16_r = __builtin_msa_aver_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.aver.u.h(
  v4u32_r = __builtin_msa_aver_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.aver.u.w(
  v2u64_r = __builtin_msa_aver_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.aver.u.d(

  v16i8_r = __builtin_msa_bclr_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.bclr.b(
  v8i16_r = __builtin_msa_bclr_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.bclr.h(
  v4i32_r = __builtin_msa_bclr_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.bclr.w(
  v2i64_r = __builtin_msa_bclr_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.bclr.d(

  v16i8_r = __builtin_msa_bclri_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.bclri.b(
  v8i16_r = __builtin_msa_bclri_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.bclri.h(
  v4i32_r = __builtin_msa_bclri_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.bclri.w(
  v2i64_r = __builtin_msa_bclri_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.bclri.d(

  v16i8_r = __builtin_msa_binsl_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.binsl.b(
  v8i16_r = __builtin_msa_binsl_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.binsl.h(
  v4i32_r = __builtin_msa_binsl_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.binsl.w(
  v2i64_r = __builtin_msa_binsl_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.binsl.d(

  v16i8_r = __builtin_msa_binsli_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.binsli.b(
  v8i16_r = __builtin_msa_binsli_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.binsli.h(
  v4i32_r = __builtin_msa_binsli_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.binsli.w(
  v2i64_r = __builtin_msa_binsli_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.binsli.d(

  v16i8_r = __builtin_msa_binsr_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.binsr.b(
  v8i16_r = __builtin_msa_binsr_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.binsr.h(
  v4i32_r = __builtin_msa_binsr_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.binsr.w(
  v2i64_r = __builtin_msa_binsr_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.binsr.d(

  v16i8_r = __builtin_msa_binsri_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.binsri.b(
  v8i16_r = __builtin_msa_binsri_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.binsri.h(
  v4i32_r = __builtin_msa_binsri_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.binsri.w(
  v2i64_r = __builtin_msa_binsri_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.binsri.d(

  v16i8_r = __builtin_msa_bmnzi_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.bmnzi.b(

  v16i8_r = __builtin_msa_bmzi_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.bmzi.b(

  v16i8_r = __builtin_msa_bneg_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.bneg.b(
  v8i16_r = __builtin_msa_bneg_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.bneg.h(
  v4i32_r = __builtin_msa_bneg_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.bneg.w(
  v2i64_r = __builtin_msa_bneg_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.bneg.d(

  v16i8_r = __builtin_msa_bnegi_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.bnegi.b(
  v8i16_r = __builtin_msa_bnegi_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.bnegi.h(
  v4i32_r = __builtin_msa_bnegi_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.bnegi.w(
  v2i64_r = __builtin_msa_bnegi_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.bnegi.d(

  v16i8_r = __builtin_msa_bset_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.bset.b(
  v8i16_r = __builtin_msa_bset_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.bset.h(
  v4i32_r = __builtin_msa_bset_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.bset.w(
  v2i64_r = __builtin_msa_bset_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.bset.d(

  v16i8_r = __builtin_msa_bseti_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.bseti.b(
  v8i16_r = __builtin_msa_bseti_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.bseti.h(
  v4i32_r = __builtin_msa_bseti_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.bseti.w(
  v2i64_r = __builtin_msa_bseti_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.bseti.d(

  v16i8_r = __builtin_msa_ceq_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.ceq.b(
  v8i16_r = __builtin_msa_ceq_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.ceq.h(
  v4i32_r = __builtin_msa_ceq_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.ceq.w(
  v2i64_r = __builtin_msa_ceq_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.ceq.d(

  v16i8_r = __builtin_msa_ceqi_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.ceqi.b(
  v8i16_r = __builtin_msa_ceqi_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.ceqi.h(
  v4i32_r = __builtin_msa_ceqi_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.ceqi.w(
  v2i64_r = __builtin_msa_ceqi_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.ceqi.d(

  v16i8_r = __builtin_msa_cle_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.cle.s.b(
  v8i16_r = __builtin_msa_cle_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.cle.s.h(
  v4i32_r = __builtin_msa_cle_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.cle.s.w(
  v2i64_r = __builtin_msa_cle_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.cle.s.d(

  v16u8_r = __builtin_msa_cle_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.cle.u.b(
  v8u16_r = __builtin_msa_cle_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.cle.u.h(
  v4u32_r = __builtin_msa_cle_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.cle.u.w(
  v2u64_r = __builtin_msa_cle_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.cle.u.d(

  v16i8_r = __builtin_msa_clei_s_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.clei.s.b(
  v8i16_r = __builtin_msa_clei_s_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.clei.s.h(
  v4i32_r = __builtin_msa_clei_s_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.clei.s.w(
  v2i64_r = __builtin_msa_clei_s_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.clei.s.d(

  v16u8_r = __builtin_msa_clei_u_b(v16u8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.clei.u.b(
  v8u16_r = __builtin_msa_clei_u_h(v8u16_a, 25); // CHECK: call <8  x i16> @llvm.mips.clei.u.h(
  v4u32_r = __builtin_msa_clei_u_w(v4u32_a, 25); // CHECK: call <4  x i32> @llvm.mips.clei.u.w(
  v2u64_r = __builtin_msa_clei_u_d(v2u64_a, 25); // CHECK: call <2  x i64> @llvm.mips.clei.u.d(

  v16i8_r = __builtin_msa_clt_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.clt.s.b(
  v8i16_r = __builtin_msa_clt_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.clt.s.h(
  v4i32_r = __builtin_msa_clt_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.clt.s.w(
  v2i64_r = __builtin_msa_clt_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.clt.s.d(

  v16u8_r = __builtin_msa_clt_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.clt.u.b(
  v8u16_r = __builtin_msa_clt_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.clt.u.h(
  v4u32_r = __builtin_msa_clt_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.clt.u.w(
  v2u64_r = __builtin_msa_clt_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.clt.u.d(

  v16i8_r = __builtin_msa_clti_s_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.clti.s.b(
  v8i16_r = __builtin_msa_clti_s_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.clti.s.h(
  v4i32_r = __builtin_msa_clti_s_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.clti.s.w(
  v2i64_r = __builtin_msa_clti_s_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.clti.s.d(

  v16u8_r = __builtin_msa_clti_u_b(v16u8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.clti.u.b(
  v8u16_r = __builtin_msa_clti_u_h(v8u16_a, 25); // CHECK: call <8  x i16> @llvm.mips.clti.u.h(
  v4u32_r = __builtin_msa_clti_u_w(v4u32_a, 25); // CHECK: call <4  x i32> @llvm.mips.clti.u.w(
  v2u64_r = __builtin_msa_clti_u_d(v2u64_a, 25); // CHECK: call <2  x i64> @llvm.mips.clti.u.d(

  int_r = __builtin_msa_copy_s_b(v16i8_a, 1); // CHECK: call i32 @llvm.mips.copy.s.b(
  int_r = __builtin_msa_copy_s_h(v8i16_a, 1); // CHECK: call i32 @llvm.mips.copy.s.h(
  int_r = __builtin_msa_copy_s_w(v4i32_a, 1); // CHECK: call i32 @llvm.mips.copy.s.w(

  int_r = __builtin_msa_copy_u_b(v16u8_a, 1); // CHECK: call i32 @llvm.mips.copy.u.b(
  int_r = __builtin_msa_copy_u_h(v8u16_a, 1); // CHECK: call i32 @llvm.mips.copy.u.h(
  int_r = __builtin_msa_copy_u_w(v4u32_a, 1); // CHECK: call i32 @llvm.mips.copy.u.w(

  v16i8_r = __builtin_msa_div_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.div.s.b(
  v8i16_r = __builtin_msa_div_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.div.s.h(
  v4i32_r = __builtin_msa_div_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.div.s.w(
  v2i64_r = __builtin_msa_div_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.div.s.d(

  v16u8_r = __builtin_msa_div_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.div.u.b(
  v8u16_r = __builtin_msa_div_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.div.u.h(
  v4u32_r = __builtin_msa_div_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.div.u.w(
  v2u64_r = __builtin_msa_div_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.div.u.d(

  v16i8_r = __builtin_msa_dotp_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.dotp.s.b(
  v8i16_r = __builtin_msa_dotp_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.dotp.s.h(
  v4i32_r = __builtin_msa_dotp_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.dotp.s.w(
  v2i64_r = __builtin_msa_dotp_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.dotp.s.d(

  v16u8_r = __builtin_msa_dotp_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.dotp.u.b(
  v8u16_r = __builtin_msa_dotp_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.dotp.u.h(
  v4u32_r = __builtin_msa_dotp_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.dotp.u.w(
  v2u64_r = __builtin_msa_dotp_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.dotp.u.d(

  v8i16_r = __builtin_msa_dpadd_s_h(v8i16_r, v16i8_a, v16i8_b); // CHECK: call <8  x i16> @llvm.mips.dpadd.s.h(
  v4i32_r = __builtin_msa_dpadd_s_w(v4i32_r, v8i16_a, v8i16_b); // CHECK: call <4  x i32> @llvm.mips.dpadd.s.w(
  v2i64_r = __builtin_msa_dpadd_s_d(v2i64_r, v4i32_a, v4i32_b); // CHECK: call <2  x i64> @llvm.mips.dpadd.s.d(

  v8u16_r = __builtin_msa_dpadd_u_h(v8u16_r, v16u8_a, v16u8_b); // CHECK: call <8  x i16> @llvm.mips.dpadd.u.h(
  v4u32_r = __builtin_msa_dpadd_u_w(v4u32_r, v8u16_a, v8u16_b); // CHECK: call <4  x i32> @llvm.mips.dpadd.u.w(
  v2u64_r = __builtin_msa_dpadd_u_d(v2u64_r, v4u32_a, v4u32_b); // CHECK: call <2  x i64> @llvm.mips.dpadd.u.d(

  v8i16_r = __builtin_msa_dpsub_s_h(v8i16_r, v16i8_a, v16i8_b); // CHECK: call <8  x i16> @llvm.mips.dpsub.s.h(
  v4i32_r = __builtin_msa_dpsub_s_w(v4i32_r, v8i16_a, v8i16_b); // CHECK: call <4  x i32> @llvm.mips.dpsub.s.w(
  v2i64_r = __builtin_msa_dpsub_s_d(v2i64_r, v4i32_a, v4i32_b); // CHECK: call <2  x i64> @llvm.mips.dpsub.s.d(

  v8u16_r = __builtin_msa_dpsub_u_h(v8u16_r, v16u8_a, v16u8_b); // CHECK: call <8  x i16> @llvm.mips.dpsub.u.h(
  v4u32_r = __builtin_msa_dpsub_u_w(v4u32_r, v8u16_a, v8u16_b); // CHECK: call <4  x i32> @llvm.mips.dpsub.u.w(
  v2u64_r = __builtin_msa_dpsub_u_d(v2u64_r, v4u32_a, v4u32_b); // CHECK: call <2  x i64> @llvm.mips.dpsub.u.d(

  v4f32_r = __builtin_msa_fadd_w(v4f32_a, v4f32_b); // CHECK: call <4 x float> @llvm.mips.fadd.w(
  v2f64_r = __builtin_msa_fadd_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fadd.d(

  v4i32_r = __builtin_msa_fceq_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fceq.w(
  v2i64_r = __builtin_msa_fceq_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fceq.d(

  v4i32_r = __builtin_msa_fclass_w(v4f32_a); // CHECK: call <4 x i32> @llvm.mips.fclass.w(
  v2i64_r = __builtin_msa_fclass_d(v2f64_a); // CHECK: call <2 x i64> @llvm.mips.fclass.d(

  v4i32_r = __builtin_msa_fcle_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fcle.w(
  v2i64_r = __builtin_msa_fcle_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fcle.d(

  v4i32_r = __builtin_msa_fclt_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fclt.w(
  v2i64_r = __builtin_msa_fclt_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fclt.d(

  v4i32_r = __builtin_msa_fcne_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fcne.w(
  v2i64_r = __builtin_msa_fcne_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fcne.d(

  v4f32_r = __builtin_msa_fdiv_w(v4f32_a, v4f32_b); // CHECK: call <4 x float> @llvm.mips.fdiv.w(
  v2f64_r = __builtin_msa_fdiv_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fdiv.d(

  v4f32_r = __builtin_msa_fexp2_w(v4f32_a, v4i32_b); // CHECK: call <4 x float> @llvm.mips.fexp2.w(
  v2f64_r = __builtin_msa_fexp2_d(v2f64_a, v2i64_b); // CHECK: call <2 x double> @llvm.mips.fexp2.d(

  v4f32_r = __builtin_msa_ffint_s_w(v4i32_a); // CHECK: call <4 x float> @llvm.mips.ffint.s.w(
  v2f64_r = __builtin_msa_ffint_s_d(v2i64_a); // CHECK: call <2 x double> @llvm.mips.ffint.s.d(

  v4f32_r = __builtin_msa_ffint_u_w(v4i32_a); // CHECK: call <4 x float> @llvm.mips.ffint.u.w(
  v2f64_r = __builtin_msa_ffint_u_d(v2i64_a); // CHECK: call <2 x double> @llvm.mips.ffint.u.d(

  v4f32_r = __builtin_msa_ffql_w(v8i16_a); // CHECK: call <4 x float> @llvm.mips.ffql.w(
  v2f64_r = __builtin_msa_ffql_d(v4i32_a); // CHECK: call <2 x double> @llvm.mips.ffql.d(

  v4f32_r = __builtin_msa_ffqr_w(v8i16_a); // CHECK: call <4 x float> @llvm.mips.ffqr.w(
  v2f64_r = __builtin_msa_ffqr_d(v4i32_a); // CHECK: call <2 x double> @llvm.mips.ffqr.d(

  v16i8_r = __builtin_msa_fill_b(3); // CHECK: call <16 x i8>  @llvm.mips.fill.b(
  v8i16_r = __builtin_msa_fill_h(3); // CHECK: call <8  x i16> @llvm.mips.fill.h(
  v4i32_r = __builtin_msa_fill_w(3); // CHECK: call <4  x i32> @llvm.mips.fill.w(

  v4f32_r = __builtin_msa_flog2_w(v8f16_a); // CHECK: call <4 x float>  @llvm.mips.flog2.w(
  v2f64_r = __builtin_msa_flog2_d(v4f32_a); // CHECK: call <2 x double> @llvm.mips.flog2.d(

  v4f32_r = __builtin_msa_fmadd_w(v8f16_r, v8f16_a, v8f16_b); // CHECK: call <4 x float>  @llvm.mips.fmadd.w(
  v2f64_r = __builtin_msa_fmadd_d(v4f32_r, v4f32_a, v4f32_b); // CHECK: call <2 x double> @llvm.mips.fmadd.d(

  v4f32_r = __builtin_msa_fmax_w(v4f32_a, v4f32_b); // CHECK: call <4 x float>  @llvm.mips.fmax.w(
  v2f64_r = __builtin_msa_fmax_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fmax.d(

  v4f32_r = __builtin_msa_fmax_a_w(v4f32_a, v4f32_b); // CHECK: call <4 x float>  @llvm.mips.fmax.a.w(
  v2f64_r = __builtin_msa_fmax_a_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fmax.a.d(

  v4f32_r = __builtin_msa_fmin_w(v4f32_a, v4f32_b); // CHECK: call <4 x float>  @llvm.mips.fmin.w(
  v2f64_r = __builtin_msa_fmin_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fmin.d(

  v4f32_r = __builtin_msa_fmin_a_w(v4f32_a, v4f32_b); // CHECK: call <4 x float>  @llvm.mips.fmin.a.w(
  v2f64_r = __builtin_msa_fmin_a_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fmin.a.d(

  v4f32_r = __builtin_msa_fmsub_w(v8f16_r, v8f16_a, v8f16_b); // CHECK: call <4 x float>  @llvm.mips.fmsub.w(
  v2f64_r = __builtin_msa_fmsub_d(v4f32_r, v4f32_a, v4f32_b); // CHECK: call <2 x double> @llvm.mips.fmsub.d(

  v4f32_r = __builtin_msa_fmul_w(v4f32_a, v4f32_b); // CHECK: call <4 x float>  @llvm.mips.fmul.w(
  v2f64_r = __builtin_msa_fmul_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fmul.d(

  v4f32_r = __builtin_msa_frint_w(v8f16_a); // CHECK: call <4 x float>  @llvm.mips.frint.w(
  v2f64_r = __builtin_msa_frint_d(v4f32_a); // CHECK: call <2 x double> @llvm.mips.frint.d(

  v4f32_r = __builtin_msa_frcp_w(v8f16_a); // CHECK: call <4 x float>  @llvm.mips.frcp.w(
  v2f64_r = __builtin_msa_frcp_d(v4f32_a); // CHECK: call <2 x double> @llvm.mips.frcp.d(

  v4f32_r = __builtin_msa_frsqrt_w(v8f16_a); // CHECK: call <4 x float>  @llvm.mips.frsqrt.w(
  v2f64_r = __builtin_msa_frsqrt_d(v4f32_a); // CHECK: call <2 x double> @llvm.mips.frsqrt.d(

  v4i32_r = __builtin_msa_fseq_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fseq.w(
  v2i64_r = __builtin_msa_fseq_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fseq.d(

  v4i32_r = __builtin_msa_fsle_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fsle.w(
  v2i64_r = __builtin_msa_fsle_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fsle.d(

  v4i32_r = __builtin_msa_fslt_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fslt.w(
  v2i64_r = __builtin_msa_fslt_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fslt.d(

  v4i32_r = __builtin_msa_fsne_w(v4f32_a, v4f32_b); // CHECK: call <4 x i32> @llvm.mips.fsne.w(
  v2i64_r = __builtin_msa_fsne_d(v2f64_a, v2f64_b); // CHECK: call <2 x i64> @llvm.mips.fsne.d(

  v4f32_r = __builtin_msa_fsqrt_w(v8f16_a); // CHECK: call <4 x float>  @llvm.mips.fsqrt.w(
  v2f64_r = __builtin_msa_fsqrt_d(v4f32_a); // CHECK: call <2 x double> @llvm.mips.fsqrt.d(

  v4f32_r = __builtin_msa_fsub_w(v4f32_a, v4f32_b); // CHECK: call <4 x float>  @llvm.mips.fsub.w(
  v2f64_r = __builtin_msa_fsub_d(v2f64_a, v2f64_b); // CHECK: call <2 x double> @llvm.mips.fsub.d(

  v4i32_r = __builtin_msa_ftint_s_w(v4f32_a); // CHECK: call <4 x i32> @llvm.mips.ftint.s.w(
  v2i64_r = __builtin_msa_ftint_s_d(v2f64_a); // CHECK: call <2 x i64> @llvm.mips.ftint.s.d(

  v4i32_r = __builtin_msa_ftint_u_w(v4f32_a); // CHECK: call <4 x i32> @llvm.mips.ftint.u.w(
  v2i64_r = __builtin_msa_ftint_u_d(v2f64_a); // CHECK: call <2 x i64> @llvm.mips.ftint.u.d(

  v8i16_r = __builtin_msa_ftq_h(v4f32_a, v4f32_b); // CHECK: call <8 x i16> @llvm.mips.ftq.h(
  v4i32_r = __builtin_msa_ftq_w(v2f64_a, v2f64_b); // CHECK: call <4 x i32> @llvm.mips.ftq.w(

  v16i8_r = __builtin_msa_ilvev_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.ilvev.b(
  v8i16_r = __builtin_msa_ilvev_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.ilvev.h(
  v4i32_r = __builtin_msa_ilvev_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.ilvev.w(
  v2i64_r = __builtin_msa_ilvev_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.ilvev.d(

  v16i8_r = __builtin_msa_ilvl_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.ilvl.b(
  v8i16_r = __builtin_msa_ilvl_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.ilvl.h(
  v4i32_r = __builtin_msa_ilvl_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.ilvl.w(
  v2i64_r = __builtin_msa_ilvl_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.ilvl.d(

  v16i8_r = __builtin_msa_ilvod_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.ilvod.b(
  v8i16_r = __builtin_msa_ilvod_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.ilvod.h(
  v4i32_r = __builtin_msa_ilvod_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.ilvod.w(
  v2i64_r = __builtin_msa_ilvod_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.ilvod.d(

  v16i8_r = __builtin_msa_ilvr_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.ilvr.b(
  v8i16_r = __builtin_msa_ilvr_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.ilvr.h(
  v4i32_r = __builtin_msa_ilvr_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.ilvr.w(
  v2i64_r = __builtin_msa_ilvr_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.ilvr.d(

  v16i8_r = __builtin_msa_ldi_b(3); // CHECK: call <16 x i8>  @llvm.mips.ldi.b(
  v8i16_r = __builtin_msa_ldi_h(3); // CHECK: call <8  x i16> @llvm.mips.ldi.h(
  v4i32_r = __builtin_msa_ldi_w(3); // CHECK: call <4  x i32> @llvm.mips.ldi.w(
  v2i64_r = __builtin_msa_ldi_d(3); // CHECK: call <2  x i64> @llvm.mips.ldi.d(

  v8i16_r = __builtin_msa_madd_q_h(v8i16_r, v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.madd.q.h(
  v4i32_r = __builtin_msa_madd_q_w(v4i32_r, v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.madd.q.w(

  v8i16_r = __builtin_msa_maddr_q_h(v8i16_r, v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.maddr.q.h(
  v4i32_r = __builtin_msa_maddr_q_w(v4i32_r, v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.maddr.q.w(

  v16i8_r = __builtin_msa_maddv_b(v16i8_r, v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.maddv.b(
  v8i16_r = __builtin_msa_maddv_h(v8i16_r, v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.maddv.h(
  v4i32_r = __builtin_msa_maddv_w(v4i32_r, v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.maddv.w(
  v2i64_r = __builtin_msa_maddv_d(v2i64_r, v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.maddv.d(

  v16i8_r = __builtin_msa_max_a_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.max.a.b(
  v8i16_r = __builtin_msa_max_a_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.max.a.h(
  v4i32_r = __builtin_msa_max_a_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.max.a.w(
  v2i64_r = __builtin_msa_max_a_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.max.a.d(

  v16i8_r = __builtin_msa_max_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.max.s.b(
  v8i16_r = __builtin_msa_max_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.max.s.h(
  v4i32_r = __builtin_msa_max_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.max.s.w(
  v2i64_r = __builtin_msa_max_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.max.s.d(

  v16u8_r = __builtin_msa_max_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.max.u.b(
  v8u16_r = __builtin_msa_max_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.max.u.h(
  v4u32_r = __builtin_msa_max_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.max.u.w(
  v2u64_r = __builtin_msa_max_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.max.u.d(

  v16i8_r = __builtin_msa_maxi_s_b(v16i8_a, 2); // CHECK: call <16 x i8>  @llvm.mips.maxi.s.b(
  v8i16_r = __builtin_msa_maxi_s_h(v8i16_a, 2); // CHECK: call <8  x i16> @llvm.mips.maxi.s.h(
  v4i32_r = __builtin_msa_maxi_s_w(v4i32_a, 2); // CHECK: call <4  x i32> @llvm.mips.maxi.s.w(
  v2i64_r = __builtin_msa_maxi_s_d(v2i64_a, 2); // CHECK: call <2  x i64> @llvm.mips.maxi.s.d(

  v16u8_r = __builtin_msa_maxi_u_b(v16u8_a, 2); // CHECK: call <16 x i8>  @llvm.mips.maxi.u.b(
  v8u16_r = __builtin_msa_maxi_u_h(v8u16_a, 2); // CHECK: call <8  x i16> @llvm.mips.maxi.u.h(
  v4u32_r = __builtin_msa_maxi_u_w(v4u32_a, 2); // CHECK: call <4  x i32> @llvm.mips.maxi.u.w(
  v2u64_r = __builtin_msa_maxi_u_d(v2u64_a, 2); // CHECK: call <2  x i64> @llvm.mips.maxi.u.d(

  v16i8_r = __builtin_msa_min_a_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.min.a.b(
  v8i16_r = __builtin_msa_min_a_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.min.a.h(
  v4i32_r = __builtin_msa_min_a_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.min.a.w(
  v2i64_r = __builtin_msa_min_a_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.min.a.d(

  v16i8_r = __builtin_msa_min_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.min.s.b(
  v8i16_r = __builtin_msa_min_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.min.s.h(
  v4i32_r = __builtin_msa_min_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.min.s.w(
  v2i64_r = __builtin_msa_min_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.min.s.d(

  v16u8_r = __builtin_msa_min_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.min.u.b(
  v8u16_r = __builtin_msa_min_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.min.u.h(
  v4u32_r = __builtin_msa_min_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.min.u.w(
  v2u64_r = __builtin_msa_min_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.min.u.d(

  v16i8_r = __builtin_msa_mini_s_b(v16i8_a, 2); // CHECK: call <16 x i8>  @llvm.mips.mini.s.b(
  v8i16_r = __builtin_msa_mini_s_h(v8i16_a, 2); // CHECK: call <8  x i16> @llvm.mips.mini.s.h(
  v4i32_r = __builtin_msa_mini_s_w(v4i32_a, 2); // CHECK: call <4  x i32> @llvm.mips.mini.s.w(
  v2i64_r = __builtin_msa_mini_s_d(v2i64_a, 2); // CHECK: call <2  x i64> @llvm.mips.mini.s.d(

  v16u8_r = __builtin_msa_mini_u_b(v16u8_a, 2); // CHECK: call <16 x i8>  @llvm.mips.mini.u.b(
  v8u16_r = __builtin_msa_mini_u_h(v8u16_a, 2); // CHECK: call <8  x i16> @llvm.mips.mini.u.h(
  v4u32_r = __builtin_msa_mini_u_w(v4u32_a, 2); // CHECK: call <4  x i32> @llvm.mips.mini.u.w(
  v2u64_r = __builtin_msa_mini_u_d(v2u64_a, 2); // CHECK: call <2  x i64> @llvm.mips.mini.u.d(

  v16i8_r = __builtin_msa_mod_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.mod.s.b(
  v8i16_r = __builtin_msa_mod_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.mod.s.h(
  v4i32_r = __builtin_msa_mod_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.mod.s.w(
  v2i64_r = __builtin_msa_mod_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.mod.s.d(

  v16u8_r = __builtin_msa_mod_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.mod.u.b(
  v8u16_r = __builtin_msa_mod_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.mod.u.h(
  v4u32_r = __builtin_msa_mod_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.mod.u.w(
  v2u64_r = __builtin_msa_mod_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.mod.u.d(

  v8i16_r = __builtin_msa_msub_q_h(v8i16_r, v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.msub.q.h(
  v4i32_r = __builtin_msa_msub_q_w(v4i32_r, v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.msub.q.w(

  v8i16_r = __builtin_msa_msubr_q_h(v8i16_r, v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.msubr.q.h(
  v4i32_r = __builtin_msa_msubr_q_w(v4i32_r, v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.msubr.q.w(

  v16i8_r = __builtin_msa_msubv_b(v16i8_r, v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.msubv.b(
  v8i16_r = __builtin_msa_msubv_h(v8i16_r, v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.msubv.h(
  v4i32_r = __builtin_msa_msubv_w(v4i32_r, v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.msubv.w(
  v2i64_r = __builtin_msa_msubv_d(v2i64_r, v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.msubv.d(

  v8i16_r = __builtin_msa_mul_q_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.mul.q.h(
  v4i32_r = __builtin_msa_mul_q_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.mul.q.w(

  v8i16_r = __builtin_msa_mulr_q_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.mulr.q.h(
  v4i32_r = __builtin_msa_mulr_q_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.mulr.q.w(

  v16i8_r = __builtin_msa_mulv_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.mulv.b(
  v8i16_r = __builtin_msa_mulv_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.mulv.h(
  v4i32_r = __builtin_msa_mulv_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.mulv.w(
  v2i64_r = __builtin_msa_mulv_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.mulv.d(

  v16i8_r = __builtin_msa_nloc_b(v16i8_a); // CHECK: call <16 x i8>  @llvm.mips.nloc.b(
  v8i16_r = __builtin_msa_nloc_h(v8i16_a); // CHECK: call <8  x i16> @llvm.mips.nloc.h(
  v4i32_r = __builtin_msa_nloc_w(v4i32_a); // CHECK: call <4  x i32> @llvm.mips.nloc.w(
  v2i64_r = __builtin_msa_nloc_d(v2i64_a); // CHECK: call <2  x i64> @llvm.mips.nloc.d(

  v16i8_r = __builtin_msa_nlzc_b(v16i8_a); // CHECK: call <16 x i8>  @llvm.mips.nlzc.b(
  v8i16_r = __builtin_msa_nlzc_h(v8i16_a); // CHECK: call <8  x i16> @llvm.mips.nlzc.h(
  v4i32_r = __builtin_msa_nlzc_w(v4i32_a); // CHECK: call <4  x i32> @llvm.mips.nlzc.w(
  v2i64_r = __builtin_msa_nlzc_d(v2i64_a); // CHECK: call <2  x i64> @llvm.mips.nlzc.d(

  v16i8_r = __builtin_msa_nori_b(v16i8_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(
  v8i16_r = __builtin_msa_nori_b(v8i16_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(
  v4i32_r = __builtin_msa_nori_b(v4i32_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(
  v2i64_r = __builtin_msa_nori_b(v2i64_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(

  v16u8_r = __builtin_msa_nori_b(v16u8_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(
  v8u16_r = __builtin_msa_nori_b(v8u16_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(
  v4u32_r = __builtin_msa_nori_b(v4u32_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(
  v2u64_r = __builtin_msa_nori_b(v2u64_a, 25); // CHECK: call <16 x i8> @llvm.mips.nori.b(

  v16i8_r = __builtin_msa_ori_b(v16i8_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(
  v8i16_r = __builtin_msa_ori_b(v8i16_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(
  v4i32_r = __builtin_msa_ori_b(v4i32_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(
  v2i64_r = __builtin_msa_ori_b(v2i64_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(

  v16u8_r = __builtin_msa_ori_b(v16u8_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(
  v8u16_r = __builtin_msa_ori_b(v8u16_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(
  v4u32_r = __builtin_msa_ori_b(v4u32_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(
  v2u64_r = __builtin_msa_ori_b(v2u64_a, 25); // CHECK: call <16 x i8> @llvm.mips.ori.b(

  v16i8_r = __builtin_msa_pckev_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.pckev.b(
  v8i16_r = __builtin_msa_pckev_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.pckev.h(
  v4i32_r = __builtin_msa_pckev_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.pckev.w(
  v2i64_r = __builtin_msa_pckev_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.pckev.d(

  v16i8_r = __builtin_msa_pckod_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.pckod.b(
  v8i16_r = __builtin_msa_pckod_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.pckod.h(
  v4i32_r = __builtin_msa_pckod_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.pckod.w(
  v2i64_r = __builtin_msa_pckod_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.pckod.d(

  v16i8_r = __builtin_msa_pcnt_b(v16i8_a); // CHECK: call <16 x i8>  @llvm.mips.pcnt.b(
  v8i16_r = __builtin_msa_pcnt_h(v8i16_a); // CHECK: call <8  x i16> @llvm.mips.pcnt.h(
  v4i32_r = __builtin_msa_pcnt_w(v4i32_a); // CHECK: call <4  x i32> @llvm.mips.pcnt.w(
  v2i64_r = __builtin_msa_pcnt_d(v2i64_a); // CHECK: call <2  x i64> @llvm.mips.pcnt.d(

  v16i8_r = __builtin_msa_sat_s_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.sat.s.b(
  v8i16_r = __builtin_msa_sat_s_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.sat.s.h(
  v4i32_r = __builtin_msa_sat_s_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.sat.s.w(
  v2i64_r = __builtin_msa_sat_s_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.sat.s.d(

  v16i8_r = __builtin_msa_sat_u_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.sat.u.b(
  v8i16_r = __builtin_msa_sat_u_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.sat.u.h(
  v4i32_r = __builtin_msa_sat_u_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.sat.u.w(
  v2i64_r = __builtin_msa_sat_u_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.sat.u.d(

  v16i8_r = __builtin_msa_shf_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.shf.b(
  v8i16_r = __builtin_msa_shf_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.shf.h(
  v4i32_r = __builtin_msa_shf_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.shf.w(

  v16i8_r = __builtin_msa_sld_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.sld.b(
  v8i16_r = __builtin_msa_sld_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.sld.h(
  v4i32_r = __builtin_msa_sld_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.sld.w(
  v2i64_r = __builtin_msa_sld_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.sld.d(

  v16i8_r = __builtin_msa_sldi_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.sldi.b(
  v8i16_r = __builtin_msa_sldi_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.sldi.h(
  v4i32_r = __builtin_msa_sldi_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.sldi.w(
  v2i64_r = __builtin_msa_sldi_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.sldi.d(

  v16i8_r = __builtin_msa_sll_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.sll.b(
  v8i16_r = __builtin_msa_sll_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.sll.h(
  v4i32_r = __builtin_msa_sll_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.sll.w(
  v2i64_r = __builtin_msa_sll_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.sll.d(

  v16i8_r = __builtin_msa_slli_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.slli.b(
  v8i16_r = __builtin_msa_slli_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.slli.h(
  v4i32_r = __builtin_msa_slli_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.slli.w(
  v2i64_r = __builtin_msa_slli_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.slli.d(

  v16i8_r = __builtin_msa_splat_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.splat.b(
  v8i16_r = __builtin_msa_splat_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.splat.h(
  v4i32_r = __builtin_msa_splat_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.splat.w(
  v2i64_r = __builtin_msa_splat_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.splat.d(

  v16i8_r = __builtin_msa_splati_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.splati.b(
  v8i16_r = __builtin_msa_splati_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.splati.h(
  v4i32_r = __builtin_msa_splati_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.splati.w(
  v2i64_r = __builtin_msa_splati_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.splati.d(

  v16i8_r = __builtin_msa_sra_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.sra.b(
  v8i16_r = __builtin_msa_sra_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.sra.h(
  v4i32_r = __builtin_msa_sra_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.sra.w(
  v2i64_r = __builtin_msa_sra_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.sra.d(

  v16i8_r = __builtin_msa_srai_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.srai.b(
  v8i16_r = __builtin_msa_srai_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.srai.h(
  v4i32_r = __builtin_msa_srai_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.srai.w(
  v2i64_r = __builtin_msa_srai_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.srai.d(

  v16i8_r = __builtin_msa_srl_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.srl.b(
  v8i16_r = __builtin_msa_srl_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.srl.h(
  v4i32_r = __builtin_msa_srl_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.srl.w(
  v2i64_r = __builtin_msa_srl_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.srl.d(

  v16i8_r = __builtin_msa_srli_b(v16i8_a, 3); // CHECK: call <16 x i8>  @llvm.mips.srli.b(
  v8i16_r = __builtin_msa_srli_h(v8i16_a, 3); // CHECK: call <8  x i16> @llvm.mips.srli.h(
  v4i32_r = __builtin_msa_srli_w(v4i32_a, 3); // CHECK: call <4  x i32> @llvm.mips.srli.w(
  v2i64_r = __builtin_msa_srli_d(v2i64_a, 3); // CHECK: call <2  x i64> @llvm.mips.srli.d(

  v16i8_r = __builtin_msa_subs_s_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.subs.s.b(
  v8i16_r = __builtin_msa_subs_s_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.subs.s.h(
  v4i32_r = __builtin_msa_subs_s_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.subs.s.w(
  v2i64_r = __builtin_msa_subs_s_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.subs.s.d(

  v16u8_r = __builtin_msa_subs_u_b(v16u8_a, v16u8_b); // CHECK: call <16 x i8>  @llvm.mips.subs.u.b(
  v8u16_r = __builtin_msa_subs_u_h(v8u16_a, v8u16_b); // CHECK: call <8  x i16> @llvm.mips.subs.u.h(
  v4u32_r = __builtin_msa_subs_u_w(v4u32_a, v4u32_b); // CHECK: call <4  x i32> @llvm.mips.subs.u.w(
  v2u64_r = __builtin_msa_subs_u_d(v2u64_a, v2u64_b); // CHECK: call <2  x i64> @llvm.mips.subs.u.d(

  v16i8_r = __builtin_msa_subv_b(v16i8_a, v16i8_b); // CHECK: call <16 x i8>  @llvm.mips.subv.b(
  v8i16_r = __builtin_msa_subv_h(v8i16_a, v8i16_b); // CHECK: call <8  x i16> @llvm.mips.subv.h(
  v4i32_r = __builtin_msa_subv_w(v4i32_a, v4i32_b); // CHECK: call <4  x i32> @llvm.mips.subv.w(
  v2i64_r = __builtin_msa_subv_d(v2i64_a, v2i64_b); // CHECK: call <2  x i64> @llvm.mips.subv.d(

  v16i8_r = __builtin_msa_subvi_b(v16i8_a, 25); // CHECK: call <16 x i8>  @llvm.mips.subvi.b(
  v8i16_r = __builtin_msa_subvi_h(v8i16_a, 25); // CHECK: call <8  x i16> @llvm.mips.subvi.h(
  v4i32_r = __builtin_msa_subvi_w(v4i32_a, 25); // CHECK: call <4  x i32> @llvm.mips.subvi.w(
  v2i64_r = __builtin_msa_subvi_d(v2i64_a, 25); // CHECK: call <2  x i64> @llvm.mips.subvi.d(

  v16i8_r = __builtin_msa_xori_b(v16i8_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(
  v8i16_r = __builtin_msa_xori_b(v8i16_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(
  v4i32_r = __builtin_msa_xori_b(v4i32_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(
  v2i64_r = __builtin_msa_xori_b(v2i64_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(

  v16u8_r = __builtin_msa_xori_b(v16u8_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(
  v8u16_r = __builtin_msa_xori_b(v8u16_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(
  v4u32_r = __builtin_msa_xori_b(v4u32_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(
  v2u64_r = __builtin_msa_xori_b(v2u64_a, 25); // CHECK: call <16 x i8> @llvm.mips.xori.b(

}
