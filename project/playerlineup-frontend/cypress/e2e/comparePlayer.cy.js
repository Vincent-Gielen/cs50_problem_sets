describe('Add and remove player', () => {

  beforeEach(() => {
    cy.login('robin@hogent.be', '12345678');
  });

  it('should compare 2 players', () => {
    cy.visit('http://localhost:5173/'); // 👈 1

    cy.get('[data-cy=select_player1]').select('Kobe Bryant - Shooting Guard'); // 👈 2
    cy.get('[data-cy=select_player2]').select('Kevin Durant - Small Forward'); // 👈 2

    cy.get('[data-cy=stats_table]').should('exist');

  });

  it('should display alert if not 2 players', () => {
    cy.visit('http://localhost:5173/'); // 👈 1

    cy.get('[data-cy=select_player1]').select('Kobe Bryant - Shooting Guard'); // 👈 2

    cy.get('[data-cy=two_players_message]').should('exist');
  });

  it('should display alert if a player is deselected', () => {
    cy.visit('http://localhost:5173/'); // 👈 1

    cy.get('[data-cy=select_player1]').select('Kobe Bryant - Shooting Guard'); // 👈 2
    cy.get('[data-cy=select_player2]').select('Kevin Durant - Small Forward'); // 👈 2

    cy.get('[data-cy=stats_table]').should('exist');

    cy.get('[data-cy=select_player1]').select('');

    cy.get('[data-cy=two_players_message]').should('exist');
  });
});
