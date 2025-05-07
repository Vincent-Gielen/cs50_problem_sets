// cypress/e2e/addTransaction.cy.js
describe('Add and remove player', () => {

  beforeEach(() => {
    cy.login('robin@hogent.be', '12345678');
  });

  it('should add a player', () => {
    cy.visit('http://localhost:5173/players/add'); // 👈 1

    cy.get('[data-cy=name_input]').type('Tester'); // 👈 2
    cy.get('[data-cy=position_input]').select('Small Forward'); // 👈 2
    cy.get('body').click(0, 0);
    cy.get('[data-cy=submit_player]').click(); // 👈 3

    cy.get('[data-cy=players_search_input]').type('Tester');
    cy.get('[data-cy=players_search_btn]').click();
    cy.get('[data-cy=player_name]').eq(0).contains('Tester'); // 👈 4
    cy.get('[data-cy=player_position]').eq(0).contains('Small Forward'); // 👈 5
    cy.get('[data-cy=player]').should('have.length', 1); // 👈 6
  });

  it('should remove the player', () => {
    cy.visit('http://localhost:5173/players/'); // 👈 1
    cy.get('[data-cy=players_search_input]').type('Tester');
    cy.get('[data-cy=players_search_btn]').click();
    cy.get('[data-cy=player_remove_btn]').eq(0).click(); // 👈 2
    cy.get('[data-cy=player]').should('have.length', 0); // 👈 3
  });
});
