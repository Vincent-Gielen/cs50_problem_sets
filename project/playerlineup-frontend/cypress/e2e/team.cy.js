describe('Player list', () => {

  beforeEach(() => {
    cy.login('robin@hogent.be', '12345678');
  });

  it('should show the teams', () => {
    // 👇 1
    cy.intercept(
      'GET',
      'http://localhost:9000/api/teams',
      { fixture: 'teams.json' },
    );

    // 👇 2
    cy.visit('http://localhost:5173/teams');
    cy.get('[data-cy=team]').should('have.length', 1);
    cy.get('[data-cy=team_name]').eq(0).contains('Los Angeles Lakers');
  });

  it('should show a loading indicator for a very slow response', () => {
    cy.intercept(
      'http://localhost:9000/api/teams', // 👈 1
      // 👇 2
      (req) => {
        req.on('response', (res) => {
          res.setDelay(1000);
        });
      },
    ).as('slowResponse'); // 👈 5
    cy.visit('http://localhost:5173/teams'); // 👈 3
    cy.get('[data-cy=loader]').should('be.visible'); // 👈 4
    cy.wait('@slowResponse'); // 👈 6
    cy.get('[data-cy=loader]').should('not.exist'); // 👈 7
  });

  it('should show all teams with Los', () => {
    cy.intercept(
      'GET',
      'http://localhost:9000/api/teams',
      { fixture: 'teams.json' }, // 👈
    );
    cy.visit('http://localhost:5173/teams');
    
    cy.get('[data-cy=teams_search_input]').type('Los');
    cy.get('[data-cy=teams_search_btn]').click();
  
    cy.get('[data-cy=team]').should('have.length', 1);
    cy.get('[data-cy=team_name]')
      .eq(0)
      .contains(/Los Angeles Lakers/);
  });
  
  it('should show a message when no teams are found', () => {

    cy.visit('http://localhost:5173/teams');
  
    cy.get('[data-cy=teams_search_input]').type('xyz');
    cy.get('[data-cy=teams_search_btn]').click();
  
    cy.get('[data-cy=no_teams_message]').should('exist');
  });
  
  it('should show an error if the API call fails', () => {
    cy.intercept('GET', 'http://localhost:9000/api/teams', {
      statusCode: 500,
      body: {
        error: 'Internal server error',
      },
    });
    cy.visit('http://localhost:5173/teams');
  
    cy.get('[data-cy=axios_error_message').should('exist');
  });
  
});
