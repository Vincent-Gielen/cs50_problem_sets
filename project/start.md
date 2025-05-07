## Requirements

I expect the following software to be installed:

- [NodeJS](https://nodejs.org)
- [Yarn](https://yarnpkg.com)
- [MySQL Community Server](https://dev.mysql.com/downloads/mysql/)

## Back-end

### Starting

Create a `.env` file as follows:
Complete the file with your credentials, secret, etc.

```bash
NODE_ENV=development
DATABASE_URL=mysql://<USERNAME>:<PASSWORD>@localhost:3306/<DATABASE_NAME>
AUTH_JWT_SECRET=<YOUR-JWT-SECRET>
```
- Enable Corepack: `corepack enable`
- Install dependencies: `yarn`
- Run migrations: `yarn migrate:dev`
- Start the development server: `yarn start:dev`

### Production

Same as starting, with a change starting from migrations:
- Run migrations: `yarn prisma migrate deploy`
- Build the project: `yarn build`
- Start the production server: `node build/src/index.js`

### Testing

Create a `.env.test` file as follows:
Complete the file with your credentials, secret, etc.

```bash
NODE_ENV=testing
DATABASE_URL=mysql://<USERNAME>:<PASSWORD>@localhost:3306/<DATABASE_NAME>_test
AUTH_JWT_SECRET=<YOUR-JWT-SECRET>
```

If all steps from starting have been followed, execute the following steps:
- Run migrations: `yarn migrate:test`
- *Optional* - Run the tests: `yarn test`
- Run the tests with coverage: `yarn test:coverage`
  - This generates a file in the \_\_tests\_\_/coverage folder.
  - Open `__tests__/coverage/lcov-report/index.html` in your browser to view the coverage report.

## Front-end

### Starting

Create a `.env` file as follows:

```bash
VITE_API_URL=http://localhost:9000/api
```
- Enable Corepack: `corepack enable`
- Install dependencies: `yarn install`
- Start the application: `yarn dev`

### Production

Same as starting, with a change before starting:
- Build the application: `yarn build` This creates a `dist` folder with the compiled files.

### Testing

If all steps from starting have been followed, execute the following steps:

Ensure both the backend and frontend are running (see above).
- Run the tests: `yarn test`
- Choose `E2E testing` in the Cypress window, and select in the new tab which tests you want to execute.
