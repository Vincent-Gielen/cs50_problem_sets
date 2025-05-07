/**
 * For a detailed explanation regarding each configuration property, visit:
 * https://jestjs.io/docs/configuration
 */

import type {Config} from 'jest';

const config: Config = {
  coverageProvider: 'v8',

  preset: 'ts-jest',

  testMatch: [
    '**/__tests__/**/?(*.)+(spec|test).[jt]s?(x)',
  ],

  // ...
  collectCoverageFrom: [
    './src/service/**/*.ts',
    './src/rest/**/*.ts',
  ],
  coverageDirectory: '__tests__/coverage',
  // ...
};

export default config;
