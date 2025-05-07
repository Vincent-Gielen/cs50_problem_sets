// cypress/e2e/addTransaction.cy.js
describe('Add and remove team', () => {

  beforeEach(() => {
    cy.login('robin@hogent.be', '12345678');
  });

  it('should add a team', () => {
    cy.visit('http://localhost:5173/teams/add'); // 👈 1

    cy.get('[data-cy=name_input]').type('Test Team'); // 👈 2
    cy.get('body').click(0, 0);
    cy.get('[data-cy=submit_team]').click(); // 👈 3

    cy.get('[data-cy=teams_search_input]').type('Test Team');
    cy.get('[data-cy=teams_search_btn]').click();
    cy.get('[data-cy=team_name]').eq(0).contains('Test Team'); // 👈 4
  });

  it('should remove the team', () => {
    cy.visit('http://localhost:5173/teams/'); // 👈 1
    cy.get('[data-cy=teams_search_input]').type('Test Team');
    cy.get('[data-cy=teams_search_btn]').click();
    cy.get('[data-cy=team_remove_btn]').eq(0).click(); // 👈 2
    cy.get('[data-cy=team]').should('have.length', 0); // 👈 3
  });
});
