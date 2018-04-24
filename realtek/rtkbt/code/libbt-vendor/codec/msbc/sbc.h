/*
 *
 *  Bluetooth low-complexity, subband codec (SBC) library
 *
 *  Copyright (C) 2004-2006  Marcel Holtmann <marcel@holtmann.org>
 *  Copyright (C) 2004-2005  Henryk Ploetz <henryk@ploetzli.ch>
 *  Copyright (C) 2005-2006  Brad Midgley <bmidgley@xmission.com>
 *
 *
 * This source code is subject to the terms and conditions defined in the
 * file 'LICENSE' which is part of this source code package.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 */

#ifndef __SBC_H
#define __SBC_H

#ifdef __cplusplus
extern "C" {
#endif


struct sbc_struct {
    unsigned long flags;
    unsigned short rate;
    unsigned char channels;
    unsigned char joint;
    unsigned char blocks;
    unsigned char subbands;
    unsigned char bitpool;

    void *data;
    int size;
    int len;

    unsigned long duration;

    void *priv;
};

typedef struct sbc_struct sbc_t;

int sbc_init(sbc_t *sbc);//int sbc_init(sbc_t *sbc, unsigned long flags);

int sbc_reinit(sbc_t *sbc);//int sbc_reinit(sbc_t *sbc, unsigned long flags);


int sbc_encode(sbc_t *sbc,
               void *input,
               int input_len,
               void *output,
               int output_len,
               int *written);

int sbc_decode(sbc_t *sbc,
               void *input,
               int input_len,
               void *output,
               int output_len,
               int *written);

void sbc_finish(sbc_t *sbc);

#ifdef __cplusplus
}
#endif

#endif /* __SBC_H */
