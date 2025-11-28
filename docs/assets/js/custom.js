// Custom JavaScript for MyProject2 Documentation

// Wait for DOM to be ready
document.addEventListener('DOMContentLoaded', function() {
    // Add custom functionality here

    // Example: Add copy button to code blocks (if not already present)
    // Material for MkDocs already has this, but you can enhance it

    // Example: Smooth scroll for anchor links
    document.querySelectorAll('a[href^="#"]').forEach(anchor => {
        anchor.addEventListener('click', function (e) {
            const href = this.getAttribute('href');
            if (href !== '#' && href.length > 1) {
                const target = document.querySelector(href);
                if (target) {
                    e.preventDefault();
                    target.scrollIntoView({
                        behavior: 'smooth',
                        block: 'start'
                    });
                }
            }
        });
    });

    // Example: Add keyboard shortcuts
    document.addEventListener('keydown', function(e) {
        // Press 'S' to focus search (if not already focused)
        if (e.key === 's' && e.target.tagName !== 'INPUT' && e.target.tagName !== 'TEXTAREA') {
            const searchInput = document.querySelector('.md-search__input');
            if (searchInput) {
                e.preventDefault();
                searchInput.focus();
            }
        }
    });

    // Example: Track page views (if analytics is configured)
    // You can integrate with your analytics service here

    console.log('MyProject2 Documentation loaded successfully!');
});
