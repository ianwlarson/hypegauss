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

#include <unity.h>

#include <stdio.h>
#include <time.h>

#include "hiperfgauss.h"
#include "seatuna.h"

hpg_state g_hpg;
SeaTuna_t g_seatuna;
rng_c g_rng = {.bytes = seatuna_get_bytes, .init = seatuna_init, .seed = seatuna_seed, .state = &g_seatuna};

void setUp(void)
{
    hpg_initialize(1.0, BoxMuller, &g_rng, &g_hpg);
}

void tearDown(void)
{
    // Do nothing.
}

static inline uint64_t get_tick_count(void)
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * UINT64_C(1000000000) + t.tv_nsec;
}

void test_hpg(void)
{
    const uint32_t sample_count = 1000000;
    const uint32_t seed = 1300227;
    g_hpg.rng->init(g_hpg.rng->state);
    g_hpg.rng->seed((const uint8_t *)&seed, sizeof(seed), g_hpg.rng->state);
    double sum = 0;
    float *sample = malloc(sizeof(*sample) * sample_count);
    for (int i = 0; i < sample_count; ++i) {
        hpg_sample_con_float(sample + i, &g_hpg);
        //printf("%f,", sample[i]);
        sum += sample[i];
    }

    double average = sum / sample_count;

    printf("average = %f\n", average);
    sum = 0;
    double max = 0;
    for (int i = 0; i < sample_count; ++i) {
        if (fabs(sample[i]) > max) {
            max = sample[i];
        }
        sum += (sample[i] - average) * (sample[i] - average);
    }

    double stddev = sqrt(sum / sample_count);

    printf("stddev = %f\n", stddev);
    printf("max = %f\n", max);

    uint64_t start = get_tick_count(), diff;
    for (int i = 0; i < sample_count; ++i) {
        hpg_sample_con_float(sample + i, &g_hpg);
    }
    diff = get_tick_count() - start;

	printf("elapsed time = %llu nanoseconds\n", diff);

    free(sample);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_hpg);

    return UNITY_END();
}
