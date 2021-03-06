/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "SkPaint.h"

#include "sk_paint.h"
#include "sk_types_priv.h"

//////////////////////////////////////////////////////////////////////////////////////////////////

sk_paint_t* sk_paint_new() { return (sk_paint_t*)new SkPaint; }

void sk_paint_delete(sk_paint_t* cpaint) { delete AsPaint(cpaint); }

bool sk_paint_is_antialias(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).isAntiAlias();
}

void sk_paint_set_antialias(sk_paint_t* cpaint, bool aa) {
    AsPaint(cpaint)->setAntiAlias(aa);
}

bool sk_paint_is_dither(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).isDither();
}

void sk_paint_set_dither(sk_paint_t* cpaint, bool isdither) {
    AsPaint(cpaint)->setDither(isdither);
}

bool sk_paint_is_verticaltext(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).isVerticalText();
}

void sk_paint_set_verticaltext(sk_paint_t* cpaint, bool vt) {
    AsPaint(cpaint)->setVerticalText(vt);
}

sk_color_t sk_paint_get_color(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).getColor();
}

void sk_paint_set_color(sk_paint_t* cpaint, sk_color_t c) {
    AsPaint(cpaint)->setColor(c);
}

void sk_paint_set_shader(sk_paint_t* cpaint, sk_shader_t* cshader) {
    AsPaint(cpaint)->setShader(AsShader(cshader));
}

sk_shader_t* sk_paint_get_shader(sk_paint_t* cpaint) {
    return ToShader(AsPaint(cpaint)->getShader());
}

void sk_paint_set_maskfilter(sk_paint_t* cpaint, sk_maskfilter_t* cfilter) {
    AsPaint(cpaint)->setMaskFilter(AsMaskFilter(cfilter));
}

sk_maskfilter_t* sk_paint_get_maskfilter(sk_paint_t* cpaint) {
    return ToMaskFilter(AsPaint(cpaint)->getMaskFilter());
}

void sk_paint_set_colorfilter(sk_paint_t* cpaint, sk_colorfilter_t* cfilter) {
    AsPaint(cpaint)->setColorFilter(AsColorFilter(cfilter));
}

sk_colorfilter_t* sk_paint_get_colorfilter(sk_paint_t* cpaint) {
    return ToColorFilter(AsPaint(cpaint)->getColorFilter());
}

void sk_paint_set_imagefilter(sk_paint_t* cpaint, sk_imagefilter_t* cfilter) {
    AsPaint(cpaint)->setImageFilter(AsImageFilter(cfilter));
}

sk_imagefilter_t* sk_paint_get_imagefilter(sk_paint_t* cpaint) {
    return ToImageFilter(AsPaint(cpaint)->getImageFilter());
}

bool sk_paint_is_stroke(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).getStyle() != SkPaint::kFill_Style;
}

void sk_paint_set_stroke(sk_paint_t* cpaint, bool doStroke) {
    AsPaint(cpaint)->setStyle(doStroke ? SkPaint::kStroke_Style : SkPaint::kFill_Style);
}

float sk_paint_get_stroke_width(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).getStrokeWidth();
}

void sk_paint_set_stroke_width(sk_paint_t* cpaint, float width) {
    AsPaint(cpaint)->setStrokeWidth(width);
}

float sk_paint_get_stroke_miter(const sk_paint_t* cpaint) {
    return AsPaint(*cpaint).getStrokeMiter();
}

void sk_paint_set_stroke_miter(sk_paint_t* cpaint, float miter) {
    AsPaint(cpaint)->setStrokeMiter(miter);
}

sk_stroke_cap_t sk_paint_get_stroke_cap(const sk_paint_t* cpaint) {
    sk_stroke_cap_t ccap;
    if (!find_c(AsPaint(*cpaint).getStrokeCap(), &ccap)) {
        ccap = BUTT_SK_STROKE_CAP;
    }
    return ccap;
}

void sk_paint_set_stroke_cap(sk_paint_t* cpaint, sk_stroke_cap_t ccap) {
    SkPaint::Cap skcap;
    if (find_sk(ccap, &skcap)) {
        AsPaint(cpaint)->setStrokeCap(skcap);
    } else {
        // unknown ccap
    }
}

sk_stroke_join_t sk_paint_get_stroke_join(const sk_paint_t* cpaint) {
    sk_stroke_join_t cjoin;
    if (!find_c(AsPaint(*cpaint).getStrokeJoin(), &cjoin)) {
        cjoin = MITER_SK_STROKE_JOIN;
    }
    return cjoin;
}

void sk_paint_set_stroke_join(sk_paint_t* cpaint, sk_stroke_join_t cjoin) {
    SkPaint::Join skjoin;
    if (find_sk(cjoin, &skjoin)) {
        AsPaint(cpaint)->setStrokeJoin(skjoin);
    } else {
        // unknown cjoin
    }
}

void sk_paint_set_xfermode_mode(sk_paint_t* paint, sk_xfermode_mode_t mode) {
    SkASSERT(paint);

    SkXfermode::Mode m;
    if (find_sk(mode, &m)) {
        AsPaint(paint)->setXfermodeMode(m);
    }
}

sk_xfermode_mode_t sk_paint_get_xfermode_mode(sk_paint_t* paint) {
    SkASSERT(paint);

    SkXfermode::Mode mode;
    sk_xfermode_mode_t cmode;
    if (SkXfermode::AsMode(AsPaint(paint)->getXfermode(), &mode) && find_c(mode, &cmode)) {
        return cmode;
    }
    return SRCOVER_SK_XFERMODE_MODE;
}

void sk_paint_set_filter_quality(sk_paint_t* cpaint, sk_filter_quality_t filterQuality)
{
    SkASSERT(cpaint);
    SkFilterQuality fq;
    if (find_sk(filterQuality, &fq)) {
        AsPaint(cpaint)->setFilterQuality(fq);
    }
}

sk_filter_quality_t sk_paint_get_filter_quality(sk_paint_t* cpaint)
{
    SkASSERT(cpaint);
    SkFilterQuality fq;
    sk_filter_quality_t cfq;
    fq = AsPaint(cpaint)->getFilterQuality();
    if (find_c(fq, &cfq)) {
        return cfq;
    }
    else {
        return NONE_SK_FILTER_QUALITY;
    }
}

sk_typeface_t* sk_paint_get_typeface(sk_paint_t* paint)
{
    return (sk_typeface_t*) AsPaint(paint)->getTypeface();
}

void sk_paint_set_typeface(sk_paint_t* paint, sk_typeface_t* typeface)
{
    AsPaint(paint)->setTypeface((SkTypeface*) typeface);
}

float sk_paint_get_textsize(sk_paint_t* paint)
{
    return AsPaint(paint)->getTextSize();
}

void sk_paint_set_textsize(sk_paint_t* paint, float size)
{
    AsPaint(paint)->setTextSize(size);
}

sk_text_align_t sk_paint_get_text_align(const sk_paint_t* cpaint) {
    sk_text_align_t calign;
    if (!find_c(AsPaint(*cpaint).getTextAlign(), &calign)) {
        calign = LEFT_SK_TEXT_ALIGN;
    }
    return calign;
}

void sk_paint_set_text_align(sk_paint_t* cpaint, sk_text_align_t calign) {
    SkPaint::Align skalign;
    if (find_sk(calign, &skalign)) {
        AsPaint(cpaint)->setTextAlign(skalign);
    } else {
        // unknown calign
    }
}

sk_text_encoding_t sk_paint_get_text_encoding(const sk_paint_t* cpaint) {
    sk_text_encoding_t cencoding;
    if (!find_c(AsPaint(*cpaint).getTextEncoding(), &cencoding)) {
        cencoding = UTF8_SK_TEXT_ENCODING;
    }
    return cencoding;
}

void sk_paint_set_text_encoding(sk_paint_t* cpaint, sk_text_encoding_t cencoding) {
    SkPaint::TextEncoding skencoding;
    if (find_sk(cencoding, &skencoding)) {
        AsPaint(cpaint)->setTextEncoding(skencoding);
    } else {
        // unknown cencoding
    }
}

float sk_paint_get_text_scale_x(const sk_paint_t* cpaint) {
    return AsPaint(cpaint)->getTextScaleX();
}

void sk_paint_set_text_scale_x(sk_paint_t* cpaint, float scale) {
    AsPaint(cpaint)->setTextScaleX(scale);
}

float sk_paint_get_text_skew_x(const sk_paint_t* cpaint) {
    return AsPaint(cpaint)->getTextSkewX();
}

void sk_paint_set_text_skew_x(sk_paint_t* cpaint, float skew) {
    AsPaint(cpaint)->setTextSkewX(skew);
}

size_t sk_paint_break_text(const sk_paint_t* cpaint, const void* text, size_t length, float maxWidth, float* measuredWidth) {
    return AsPaint(cpaint)->breakText(text, length, maxWidth, measuredWidth);
}

size_t sk_paint_break_utf16_text(sk_paint_t* cpaint, const void* text, size_t length, float maxWidth, float* measuredWidth) {
    SkPaint *paint = AsPaint(cpaint);
    auto encoding = paint->getTextEncoding ();
    int changed = 0;
    if (encoding != SkPaint::kUTF16_TextEncoding){
        changed = 1;
        paint->setTextEncoding(SkPaint::kUTF16_TextEncoding);
    }
    auto ret = paint->breakText(text, length * sizeof(uint16_t), maxWidth, measuredWidth);
    if (changed != 0){
        paint->setTextEncoding(encoding);
    }
    return ret;
}

float sk_paint_measure_text(const sk_paint_t* cpaint, const void* text, size_t length, sk_rect_t* bounds) {
    return AsPaint(cpaint)->measureText(text, length, AsRect(bounds));
}

float sk_paint_measure_utf16_text(sk_paint_t* cpaint, const void* text, size_t length, sk_rect_t* bounds) {
    SkPaint* paint = AsPaint(cpaint);
    auto encoding = paint->getTextEncoding ();
    int changed = 0;
    if (encoding != SkPaint::kUTF16_TextEncoding){
        changed = 1;
        paint->setTextEncoding(SkPaint::kUTF16_TextEncoding);
    }
    auto ret = paint->measureText(text, length * sizeof(uint16_t), AsRect(bounds));
    if (changed != 0){
        paint->setTextEncoding(encoding);
    }
    return ret;
}

sk_path_t* sk_paint_get_text_path(sk_paint_t* cpaint, const void* text, size_t length, float x, float y) {
    SkPath* path = new SkPath();
    AsPaint(cpaint)->getTextPath(text, length, x, y, path);
    return ToPath(path);
}

sk_path_t* sk_paint_get_utf16_text_path(sk_paint_t* cpaint, const uint16_t *text, size_t lengthInChars, float x, float y) {
    SkPaint* paint = AsPaint(cpaint);
    SkPath* path = new SkPath();

    auto encoding = paint->getTextEncoding();
    int changed = 0;
    if (encoding != SkPaint::kUTF16_TextEncoding) {
        changed = 1;
        paint->setTextEncoding(SkPaint::kUTF16_TextEncoding);
    }

    AsPaint(cpaint)->getTextPath(text, lengthInChars * sizeof(uint16_t), x, y, path);

    if (changed != 0) {
        paint->setTextEncoding(encoding);
    }

    return ToPath(path);
}

sk_path_t* sk_paint_get_pos_text_path(sk_paint_t* cpaint, const void* text, size_t length, const sk_point_t pos[]) {
    SkPath* path = new SkPath();
    AsPaint(cpaint)->getPosTextPath(text, length, reinterpret_cast<const SkPoint*>(pos), path);
    return ToPath(path);
}

sk_path_t* sk_paint_get_pos_utf16_text_path(sk_paint_t* cpaint, const uint16_t *text, size_t lengthInChars, const sk_point_t pos[]) {
    SkPaint* paint = AsPaint(cpaint);
    SkPath* path = new SkPath();

    auto encoding = paint->getTextEncoding();
    int changed = 0;
    if (encoding != SkPaint::kUTF16_TextEncoding) {
        changed = 1;
        paint->setTextEncoding(SkPaint::kUTF16_TextEncoding);
    }

    AsPaint(cpaint)->getPosTextPath(text, lengthInChars * sizeof(uint16_t), reinterpret_cast<const SkPoint*>(pos), path);

    if (changed != 0) {
        paint->setTextEncoding(encoding);
    }

    return ToPath(path);
}

float sk_paint_get_fontmetrics(sk_paint_t* cpaint, sk_fontmetrics_t* cfontmetrics, float scale)
{
    SkPaint *paint = AsPaint(cpaint);
    return paint->getFontMetrics(AsFontMetrics(cfontmetrics), scale);
}

