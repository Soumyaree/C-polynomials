pipeline {
    agent {label 'master'}

    options {
        timestamps()
        ansiColor('xterm')
    }

    stages {
        stage('Build') {
            steps {
                echo 'Building project using Makefile'
                sh '''
                    cd /home/jenkins/C-Polynomials/
                    make clean
                    make
                '''
            }
        }

        stage('Run Benchmarks & Demo') {
            steps {
                echo 'Running benchmarks and demo'
                sh '''
                    chmod +x /home/jenkins/C-Polynomials/run.sh
                    /home/jenkins/C-Polynomials/run.sh
                '''
            }
        }
    }

    post {
        always {
            echo 'Archiving logs'
            archiveArtifacts artifacts: 'logs/*.log', fingerprint: true
        }

        success {
            echo 'BUILD & BENCHMARKS COMPLETED SUCCESSFULLY'
        }

        failure {
            echo 'BUILD OR BENCHMARK FAILED'
        }
    }
}
