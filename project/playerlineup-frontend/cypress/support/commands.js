// ***********************************************
// This example commands.js shows you how to
// create various custom commands and overwrite
// existing commands.
//
// For more comprehensive examples of custom
// commands please read more here:
// https://on.cypress.io/custom-commands
// ***********************************************
//
//
// -- This is a parent command --
// Cypress.Commands.add('login', (email, password) => { ... })
//
//
// -- This is a child command --
// Cypress.Commands.add('drag', { prevSubject: 'element'}, (subject, options) => { ... })
//
//
// -- This is a dual command --
// Cypress.Commands.add('dismiss', { prevSubject: 'optional'}, (subject, options) => { ... })
//
//
// -- This will overwrite an existing command --
// Cypress.Commands.overwrite('visit', (originalFn, url, options) => { ... })
// 👇 1
Cypress.Commands.add('login', (email, password) => {
  // 👇 5
  Cypress.log({
    displayName: 'login',
  });

  cy.intercept('/api/sessions').as('login');
  cy.visit('http://localhost:5173/login'); // 👈 2

  cy.get('[data-cy=email_input]').clear(); // 👈 3
  cy.get('[data-cy=email_input]').type(email); // 👈 3

  cy.get('[data-cy=password_input]').clear(); // 👈 3
  cy.get('[data-cy=password_input]').type(password); // 👈 3

  cy.get('[data-cy=submit_btn]').click(); // 👈 4
  cy.wait('@login');
});

Cypress.Commands.add('logout', () => {
  Cypress.log({
    displayName: 'logout',
  });

  cy.visit('http://localhost:5173');
  cy.get('[data-cy=logout_btn]').click();
});

