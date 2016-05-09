/** Copyright 2016 Ian W. Larson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HIPERFGAUSS_H
#define HIPERFGAUSS_H

#include <math.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define STATE_BUFFER_SIZE 100

enum SamplerBackend {
    InverseXForm,
    AcceptanceRejection,
    BoxMuller,
    Ziggurat
};

// rng container because passing a function pointer is gross.
typedef struct {
    void *state;
    bool (*init)(void *state);
    bool (*seed)(const uint8_t *buffer, size_t buffer_size, void *state);
    bool (*bytes)(uint8_t *buffer, size_t buffer_size, void *state);
} rng_c;

typedef struct {
    rng_c *rng;
    uint32_t internal_rand_buffer[STATE_BUFFER_SIZE];
    size_t counter;
    enum SamplerBackend sampler;
    bool initialized;
    float stddev;
} hpg_state;

bool hpg_initialize(float stddev, enum SamplerBackend sampler, rng_c *rng, hpg_state *state);

bool hpg_sample_con_float(float *sample, hpg_state *state);
bool hpg_sample_dis_float(float *sample, hpg_state *state);


#endif /* HIPERFGAUSS_H */
