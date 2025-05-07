describe('General', () => {
  it('draait de applicatie', () => {
    cy.visit('http://localhost:5173');
    cy.get('h1').should('exist');
  });

  // 👇 1
  it('should login', () => {
    cy.login('robin@hogent.be', '12345678'); // 👈 2
  });
});
