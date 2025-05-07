describe('Player list', () => {

  beforeEach(() => {
    cy.login('robin@hogent.be', '12345678');
  });

  it('should show the players', () => {
    // 👇 1
    cy.intercept(
      'GET',
      'http://localhost:9000/api/players',
      { fixture: 'players.json' },
    );

    // 👇 2
    cy.visit('http://localhost:5173/players');
    cy.get('[data-cy=player]').should('have.length', 2);
    cy.get('[data-cy=player_name]').eq(0).contains('Test Player 11');
    cy.get('[data-cy=player_position]').eq(1).contains('Point Guard');
  });

  it('should show a loading indicator for a very slow response', () => {
    cy.intercept(
      'http://localhost:9000/api/players', // 👈 1
      // 👇 2
      (req) => {
        req.on('response', (res) => {
          res.setDelay(1000);
        });
      },
    ).as('slowResponse'); // 👈 5
    cy.visit('http://localhost:5173/players'); // 👈 3
    cy.get('[data-cy=loader]').should('be.visible'); // 👈 4
    cy.wait('@slowResponse'); // 👈 6
    cy.get('[data-cy=loader]').should('not.exist'); // 👈 7
  });

  it('should show all players with kobe', () => {
    cy.intercept(
      'GET',
      'http://localhost:9000/api/players',
      { fixture: 'players.json' }, // 👈
    );
    cy.visit('http://localhost:5173/players');
    
    cy.get('[data-cy=players_search_input]').type('kobe');
    cy.get('[data-cy=players_search_btn]').click();
  
    cy.get('[data-cy=player]').should('have.length', 1);
    cy.get('[data-cy=player_name]')
      .eq(0)
      .contains(/Kobe Bryant/);
  });
  
  it('should show a message when no players are found', () => {

    cy.visit('http://localhost:5173/players');
  
    cy.get('[data-cy=players_search_input]').type('xyz');
    cy.get('[data-cy=players_search_btn]').click();
  
    cy.get('[data-cy=no_players_message]').should('exist');
  });
  
  it('should show an error if the API call fails', () => {
    cy.intercept('GET', 'http://localhost:9000/api/players', {
      statusCode: 500,
      body: {
        error: 'Internal server error',
      },
    });
    cy.visit('http://localhost:5173/players');
  
    cy.get('[data-cy=axios_error_message').should('exist');
  });
  
});
