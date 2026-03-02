pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps { checkout scm }
        }

        stage('Static Analysis') {
            steps {
                // Runs Cppcheck and creates an XML report
                // --enable=all: checks everything
                // --xml: produces an XML file for Jenkins to read
                sh 'cppcheck --enable=all --xml --xml-version=2 . 2> cppcheck-results.xml'
            }
        }

        stage('Build') {
            steps {
                sh 'make clean'
                sh 'make'
            }
        }
    }
    
    post {
        always {
            // This is the correct modern way to capture Cppcheck results
            recordIssues(
                enabledForFailure: true,
                tool: cppCheck(pattern: 'cppcheck-results.xml')
            )
            // Archive the actual binary created
            archiveArtifacts artifacts: 'clienttest', fingerprint: true
        }
    }
}