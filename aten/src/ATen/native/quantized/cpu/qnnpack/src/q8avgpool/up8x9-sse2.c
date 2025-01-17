/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <assert.h>

#include <emmintrin.h>

#include <qnnpack/q8avgpool.h>

void pytorch_q8avgpool_ukernel_up8x9__sse2(
    size_t n,
    size_t ks,
    size_t kc,
    const uint8_t** input,
    const uint8_t* zero,
    uint8_t* output,
    size_t input_increment,
    size_t output_increment,
    const union pytorch_qnnp_avgpool_quantization_params
        quantization_params[RESTRICT_STATIC 1]) {
  assert(n != 0);
  assert(ks <= 9);
  assert(kc >= 8);

  const __m128i vbias =
      _mm_load_si128((const __m128i*)&quantization_params->sse2.bias);
  const __m128i vzero = _mm_setzero_si128();
  const __m128 vscale = _mm_loadu_ps(quantization_params->sse2.scale);

  do {
    const uint8_t* i0 = input[0];
    const uint8_t* i1 = input[1];
    const uint8_t* i2 = input[2];
    const uint8_t* i3 = input[3];
    const uint8_t* i4 = input[4];
    const uint8_t* i5 = input[5];
    const uint8_t* i6 = input[6];
    const uint8_t* i7 = input[7];
    const uint8_t* i8 = input[8];
    input = (const uint8_t**)((uintptr_t)input + input_increment);
    if (ks < 2) {
      i1 = zero;
    }
    if (ks <= 2) {
      i2 = zero;
    }
    if (ks < 4) {
      i3 = zero;
    }
    if (ks <= 4) {
      i4 = zero;
    }
    if (ks < 6) {
      i5 = zero;
    }
    if (ks <= 6) {
      i6 = zero;
    }
    if (ks < 8) {
      i7 = zero;
    }
    if (ks <= 8) {
      i8 = zero;
    }

    size_t k = kc;
    while (k >= 8) {
      const __m128i vi0 = _mm_loadl_epi64((const __m128i*)i0);
      i0 += 8;
      const __m128i vi1 = _mm_loadl_epi64((const __m128i*)i1);
      i1 += 8;
      const __m128i vi2 = _mm_loadl_epi64((const __m128i*)i2);
      i2 += 8;
      const __m128i vi3 = _mm_loadl_epi64((const __m128i*)i3);
      i3 += 8;
      const __m128i vi4 = _mm_loadl_epi64((const __m128i*)i4);
      i4 += 8;
      const __m128i vi5 = _mm_loadl_epi64((const __m128i*)i5);
      i5 += 8;
      const __m128i vi6 = _mm_loadl_epi64((const __m128i*)i6);
      i6 += 8;
      const __m128i vi7 = _mm_loadl_epi64((const __m128i*)i7);
      i7 += 8;
      const __m128i vi8 = _mm_loadl_epi64((const __m128i*)i8);
      i8 += 8;

      const __m128i vxi0 = _mm_unpacklo_epi8(vi0, vzero);
      const __m128i vxi1 = _mm_unpacklo_epi8(vi1, vzero);
      const __m128i vxi2 = _mm_unpacklo_epi8(vi2, vzero);
      const __m128i vxi3 = _mm_unpacklo_epi8(vi3, vzero);
      const __m128i vxi4 = _mm_unpacklo_epi8(vi4, vzero);
      const __m128i vxi5 = _mm_unpacklo_epi8(vi5, vzero);
      const __m128i vxi6 = _mm_unpacklo_epi8(vi6, vzero);
      const __m128i vxi7 = _mm_unpacklo_epi8(vi7, vzero);
      const __m128i vxi8 = _mm_unpacklo_epi8(vi8, vzero);

      const __m128i vsum018 = _mm_add_epi16(_mm_add_epi16(vxi0, vxi1), vxi8);
      const __m128i vsum23 = _mm_add_epi16(vxi2, vxi3);
      const __m128i vsum45 = _mm_add_epi16(vxi4, vxi5);
      const __m128i vsum67 = _mm_add_epi16(vxi6, vxi7);

      const __m128i vsum2345 = _mm_add_epi16(vsum23, vsum45);
      const __m128i vsum01678 = _mm_add_epi16(vsum018, vsum67);
      const __m128i vsum = _mm_add_epi16(vsum2345, vsum01678);

      const __m128i vacc_lo =
          _mm_add_epi32(vbias, _mm_unpacklo_epi16(vsum, vzero));
      const __m128i vacc_hi =
          _mm_add_epi32(vbias, _mm_unpackhi_epi16(vsum, vzero));

      const __m128 vacc_lo_f = _mm_mul_ps(_mm_cvtepi32_ps(vacc_lo), vscale);
      const __m128 vacc_hi_f = _mm_mul_ps(_mm_cvtepi32_ps(vacc_hi), vscale);

      const __m128i vscaled_lo = _mm_cvtps_epi32(vacc_lo_f);
      const __m128i vscaled_hi = _mm_cvtps_epi32(vacc_hi_f);

      __m128i vout = _mm_packs_epi32(vscaled_lo, vscaled_hi);
      vout = _mm_adds_epi16(
          vout,
          _mm_load_si128(
              (const __m128i*)&quantization_params->sse2.output_zero_point));
      vout = _mm_packus_epi16(vout, vout);
      vout = _mm_min_epu8(
          vout,
          _mm_load_si128(
              (const __m128i*)&quantization_params->sse2.output_max));
      vout = _mm_max_epu8(
          vout,
          _mm_load_si128(
              (const __m128i*)&quantization_params->sse2.output_min));

      _mm_storel_epi64((__m128i*)output, vout);
      output += 8;

      k -= 8;
    }
    if (k != 0) {
      const size_t address_decrement = 8 - k;
      i0 = (const uint8_t*)((uintptr_t)i0 - address_decrement);
      i1 = (const uint8_t*)((uintptr_t)i1 - address_decrement);
      i2 = (const uint8_t*)((uintptr_t)i2 - address_decrement);
      i3 = (const uint8_t*)((uintptr_t)i3 - address_decrement);
      i4 = (const uint8_t*)((uintptr_t)i4 - address_decrement);
      i5 = (const uint8_t*)((uintptr_t)i5 - address_decrement);
      i6 = (const uint8_t*)((uintptr_t)i6 - address_decrement);
      i7 = (const uint8_t*)((uintptr_t)i7 - address_decrement);
      i8 = (const uint8_t*)((uintptr_t)i8 - address_decrement);
      const __m128i vshift = _mm_cvtsi32_si128(8 * address_decrement);

      const __m128i vi0 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i0), vshift);
      const __m128i vi1 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i1), vshift);
      const __m128i vi2 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i2), vshift);
      const __m128i vi3 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i3), vshift);
      const __m128i vi4 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i4), vshift);
      const __m128i vi5 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i5), vshift);
      const __m128i vi6 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i6), vshift);
      const __m128i vi7 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i7), vshift);
      const __m128i vi8 =
          _mm_srl_epi64(_mm_loadl_epi64((const __m128i*)i8), vshift);

      const __m128i vxi0 = _mm_unpacklo_epi8(vi0, vzero);
      const __m128i vxi1 = _mm_unpacklo_epi8(vi1, vzero);
      const __m128i vxi2 = _mm_unpacklo_epi8(vi2, vzero);
      const __m128i vxi3 = _mm_unpacklo_epi8(vi3, vzero);
      const __m128i vxi4 = _mm_unpacklo_epi8(vi4, vzero);
      const __m128i vxi5 = _mm_unpacklo_epi8(vi5, vzero);
      const __m128i vxi6 = _mm_unpacklo_epi8(vi6, vzero);
      const __m128i vxi7 = _mm_unpacklo_epi8(vi7, vzero);
      const __m128i vxi8 = _mm_unpacklo_epi8(vi8, vzero);

      const __m128i vsum018 = _mm_add_epi16(_mm_add_epi16(vxi0, vxi1), vxi8);
      const __m128i vsum23 = _mm_add_epi16(vxi2, vxi3);
      const __m128i vsum45 = _mm_add_epi16(vxi4, vxi5);
      const __m128i vsum67 = _mm_add_epi16(vxi6, vxi7);

      const __m128i vsum2345 = _mm_add_epi16(vsum23, vsum45);
      const __m128i vsum01678 = _mm_add_epi16(vsum018, vsum67);
      const __m128i vsum = _mm_add_epi16(vsum2345, vsum01678);

      const __m128i vacc_lo =
          _mm_add_epi32(vbias, _mm_unpacklo_epi16(vsum, vzero));
      const __m128i vacc_hi =
          _mm_add_epi32(vbias, _mm_unpackhi_epi16(vsum, vzero));

      const __m128 vacc_lo_f = _mm_mul_ps(_mm_cvtepi32_ps(vacc_lo), vscale);
      const __m128 vacc_hi_f = _mm_mul_ps(_mm_cvtepi32_ps(vacc_hi), vscale);

      const __m128i vscaled_lo = _mm_cvtps_epi32(vacc_lo_f);
      const __m128i vscaled_hi = _mm_cvtps_epi32(vacc_hi_f);

      __m128i vout = _mm_packs_epi32(vscaled_lo, vscaled_hi);
      vout = _mm_adds_epi16(
          vout,
          _mm_load_si128(
              (const __m128i*)&quantization_params->sse2.output_zero_point));
      vout = _mm_packus_epi16(vout, vout);
      vout = _mm_min_epu8(
          vout,
          _mm_load_si128(
              (const __m128i*)&quantization_params->sse2.output_max));
      vout = _mm_max_epu8(
          vout,
          _mm_load_si128(
              (const __m128i*)&quantization_params->sse2.output_min));

      if (k & 4) {
        *((uint32_t*)output) = (uint32_t)_mm_cvtsi128_si32(vout);
        output += 4;
        vout = _mm_srli_epi64(vout, 32);
      }
      if (k & 2) {
        *((uint16_t*)output) = (uint16_t)_mm_extract_epi16(vout, 0);
        output += 2;
        vout = _mm_srli_epi32(vout, 16);
      }
      if (k & 1) {
        *((uint8_t*)output) = (uint8_t)_mm_cvtsi128_si32(vout);
        output += 1;
      }
    }
    output = (uint8_t*)((uintptr_t)output + output_increment);
  } while (--n != 0);
}
